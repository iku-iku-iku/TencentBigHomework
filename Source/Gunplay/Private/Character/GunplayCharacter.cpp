#include "Character/GunplayCharacter.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Component/AnimationComponent.h"
#include "Component/CharacterStatusComponent.h"
#include "Component/HoldComponent.h"
#include "Component/BloodBarComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Interface/BeHitInterface.h"
#include "Interface/BeObtainedInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager/BleedingTextManager.h"

AGunplayCharacter::AGunplayCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bAlwaysRelevant = true;
	SetReplicatingMovement(true);
	// always spawn
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	AnimationComponent = CreateDefaultSubobject<UAnimationComponent>(TEXT("Animation"));
	StatusComponent = CreateDefaultSubobject<UCharacterStatusComponent>(TEXT("Status"));
	HoldingComponent = CreateDefaultSubobject<UHoldComponent>(TEXT("Holding"));

	BloodBarComponent = CreateDefaultSubobject<UBloodBarComponent>(TEXT("Blood Bar"));
	BloodBarComponent->SetupAttachment(RootComponent);
	BloodBarComponent->SetRelativeRotation(FRotator(0));

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
}

void AGunplayCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CalculateFootIK(DeltaSeconds);

	if (HasAuthority())
	{
		AnimationComponent->SetInAir(GetMovementComponent()->IsFalling());
	}
}

void AGunplayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGunplayCharacter::Jump()
{
	Super::Jump();

	AnimationComponent->SetWantToJump(true);
}

void AGunplayCharacter::BeHit(const FHitInfo& HitInfo)
{
	check(HasAuthority())

	StatusComponent->AddHP(-HitInfo.Damage * DefenseScale());

	if (StatusComponent->GetHP() <= 0)
	{
		if (HitInfo.Hitter)
		{
			BeKilledBy(HitInfo.Hitter);
		}

		if (! bDead)
		{
			bDead = true;

			DeathEvent.Broadcast(this);
		}
	}

	FVector Dir;
	float Length;
	HitInfo.Impulse.ToDirectionAndLength(Dir, Length);
	// 力的方向上调一点，大小不变
	const FVector Force = BaseHitForceScale * Length * (Dir + FVector::UpVector).GetSafeNormal();
	GetCharacterMovement()->AddImpulse(Force, false);

	if (AGunplayCharacter* HitterCharacter = HitInfo.HitterCharacter)
	{
		// 攻击者的客户端显示相应的攻击效果
		HitterCharacter->Client_HitCharacterEffect(HitInfo);
	}
}

void AGunplayCharacter::Client_HitCharacterEffect_Implementation(const FHitInfo& HitInfo)
{
	if (UBleedingTextManager* BleedingTextManager = UBleedingTextManager::GetInstance())
	{
		BleedingTextManager->SpawnBleedingTextAt(HitInfo.HitLocation, HitInfo.Damage);
	}
}


bool AGunplayCharacter::ObtainHolding(const TSubclassOf<AActor> HoldingClass)
{
	if (UWorld* World = GetWorld())
	{
		if (AActor* Holding = World->SpawnActor(HoldingClass))
		{
			if (Holding->Implements<UBeObtainedInterface>())
			{
				IBeObtainedInterface::Execute_BeObtainedBy(Holding, this);
				return true;
			}
		}
	}
	return false;
}

void AGunplayCharacter::OnRep_WantToJump()
{
	UE_LOG(LogTemp, Warning, TEXT("OnRep Want To Jump"))
}

void AGunplayCharacter::TraceFoot(const FName& SocketName, float& OutFootOffset, FVector& OutHitLocation) const
{
	if (USkeletalMeshComponent* SkeletalMeshComponent = GetMesh())
	{
		const FVector SocketLocation = SkeletalMeshComponent->GetSocketLocation(SocketName);
		const FVector ActorLocation = GetActorLocation();
		const FVector Start = {SocketLocation.X, SocketLocation.Y, ActorLocation.Z};
		const FVector End = {SocketLocation.X, SocketLocation.Y, SocketLocation.Z - MaxFootDetectDistance};

		if (UWorld* World = GetWorld())
		{
			FHitResult HitResult;
			FCollisionQueryParams CollisionQueryParams;
			CollisionQueryParams.AddIgnoredActor(this);
			if (World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionQueryParams))
			{
				FVector_NetQuantize HitLocation = HitResult.Location;
				OutHitLocation = HitLocation;

				FVector Bottom = SkeletalMeshComponent->GetComponentLocation();
				OutFootOffset = Bottom.Z - HitLocation.Z;
			}
		}
	}
}

void AGunplayCharacter::CalculateFootIK(const float DeltaSeconds)
{
	float TempLFootOffset = 0.f, TempRFootOffset = 0.f;
	FVector LFootHitLocation(0.f), RFootHitLocation(0.f);
	TraceFoot(LFootSocketName, TempLFootOffset, LFootHitLocation);
	TraceFoot(RFootSocketName, TempRFootOffset, RFootHitLocation);

	const float HitDelta = FMath::Abs(LFootHitLocation.Z - RFootHitLocation.Z);
	const float Compensation = TempLFootOffset + TempRFootOffset;
	float TempHipOffset = HitDelta + Compensation;
	TempHipOffset = TempHipOffset > MaxHipOffset ? 0.f : TempHipOffset * -0.5f;

	TempLFootOffset += HipOffset;
	TempRFootOffset += HipOffset;

	LFootOffset = UKismetMathLibrary::FInterpTo(LFootOffset, TempLFootOffset, DeltaSeconds, FootInterpolateSpeed);
	RFootOffset = UKismetMathLibrary::FInterpTo(RFootOffset, TempRFootOffset, DeltaSeconds, FootInterpolateSpeed);
	HipOffset = UKismetMathLibrary::FInterpTo(HipOffset, TempHipOffset, DeltaSeconds, FootInterpolateSpeed);
}

float AGunplayCharacter::DefenseScale()
{
	const float Defense = StatusComponent->GetDefense();
	return 1.f - Defense / (100.f + Defense);
}
