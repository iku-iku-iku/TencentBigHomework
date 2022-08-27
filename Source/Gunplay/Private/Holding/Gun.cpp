#include "Holding/Gun.h"

#include <Camera/CameraComponent.h>

#include "DrawDebugHelpers.h"
#include "Component/CharacterStatusComponent.h"
#include "Character/GunplayCharacter.h"
#include "Component/AnimationComponent.h"
#include "Component/BeadComponent.h"
<<<<<<< HEAD
#include "Component/HoldComponent.h"
=======
#include "Component/HoldingComponent.h"
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
#include "Component/PickupComponent.h"
#include "Component/ShootComponent.h"
#include "Component/SpawnComponent.h"
#include "Components/DecalComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/Material.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AGun::AGun()
{
	bReplicates = true;
	SetReplicatingMovement(true);
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("Pickup"));
	PickupComponent->SetSocketName(AttachedSocketName);
	PickupComponent->SetupAttachment(RootComponent);

	// set default mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleMeshFinder(TEXT("/Game/Weapons/Rifle.Rifle"));
	if (RifleMeshFinder.Succeeded())
	{
		Mesh->SetSkeletalMesh(RifleMeshFinder.Object);
	}

	// set default particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PSFinder(
		TEXT("/Game/ParticleSystem/BulletImpact.BulletImpact"));
	if (PSFinder.Succeeded())
	{
		PS_BulletImpact = PSFinder.Object;
	}

	// set default sound
	static ConstructorHelpers::FObjectFinder<USoundCue> SoundFinder(TEXT("/Game/Sounds/Impacts/SC_Bullet.SC_Bullet"));
	if (SoundFinder.Succeeded())
	{
		Sd_ShootImpact = SoundFinder.Object;
	}

	SpawnComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("Spawn Component"));

	Mesh->SetCollisionResponseToChannel(ECC_GUN, ECR_Ignore);

	BeadComponent = CreateDefaultSubobject<UBeadComponent>(TEXT("Bead Component"));

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("Shoot Component"));
}


void AGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGun, BulletNum)
}

void AGun::Using(float DeltaTime)
{
	if (BulletNum > 0)
	{
		Holder->GetAnimationComponent()->SetIsShooting(true);
		ShootComponent->Shooting(PickupComponent->GetOwnerCharacter());
	}
	else
	{
		Holder->GetAnimationComponent()->SetIsShooting(false);
	}
}

void AGun::Used()
{
	Holder->GetAnimationComponent()->SetIsShooting(false);
}

void AGun::BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter)
{
	Super::BeObtainedBy_Implementation(GunplayCharacter);

	if (HasAuthority())
	{
		if (AGun* Gun = Cast<AGun>(GunplayCharacter->GetHoldingComponent()->FindHolding(GetClass())))
		{
<<<<<<< HEAD
			Gun->SetBulletNum(Gun->GetMaxBulletNum());
=======
			Gun->SetBulletNum(MaxBulletNum);
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
			Destroy();
		}
		else
		{
			PickupComponent->AttachToPlayer(GunplayCharacter);
		}
		SpawnComponent->ResetSpawner();
	}
}

void AGun::Multi_ShootEffect(const FHitResult& HitResult)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_BulletImpact, HitResult.Location);
	UGameplayStatics::PlaySound2D(GetWorld(), Sd_ShootImpact);

	if (const AActor* HitActor = HitResult.GetActor())
	{
		if (Mat_BulletHoleDecal && ! HitActor->GetClass()->IsChildOf(ACharacter::StaticClass()))
		{
			const FVector HitLocation = HitResult.Location;
			FRotator Rotator = HitResult.ImpactNormal.Rotation();
			Rotator.Roll = FMath::FRandRange(0, 360.f);

			UDecalComponent* BulletHole = UGameplayStatics::SpawnDecalAttached(
				Mat_BulletHoleDecal, BulletHoleSize, HitResult.GetComponent(), HitResult.BoneName,
				HitLocation, Rotator, EAttachLocation::KeepWorldPosition,
				BulletHoleLifeSpan);
			if (BulletHole)
			{
				BulletHole->SetFadeScreenSize(FadeScreenSize);
			}
		}
	}
}

<<<<<<< HEAD
=======
void AGun::SetMaxBullet(int32 NewValue)
{
	MaxBulletNum = NewValue;
}

>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
FVector AGun::GetBarrelLocation() const
{
	return Mesh->GetSocketLocation(BarrelSocketName);
}

float AGun::CalculateDamage(const FHitResult& HitResult) const
{
	const float RandomDeviationScale = FMath::FRandRange(-DamageDeviation, DamageDeviation);
	const float Scale = DamageScale + RandomDeviationScale;
	const float Attack = PickupComponent->GetOwnerCharacter()->GetStatus()->GetAttack();

	float Damage = Scale * Attack;

	if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(HitResult.GetActor()))
	{
		if (HitResult.BoneName.IsEqual(GunplayCharacter->GetHeadBoneName()))
		{
			Damage *= HeadShotDamageRate;
		}
	}

	return Damage;
}

bool AGun::Server_Shoot(const FHitResult& HitResult)
{
	if (BulletNum > 0) { BulletNum--; }
	else { return false; }

	const FVector ForceDir = (HitResult.TraceEnd - HitResult.TraceStart).GetSafeNormal();
	const FVector Force = ForceDir * ShootComponent->GetBaseShootForce();

	AActor* HitActor = HitResult.GetActor();
	if (IBeHitInterface* BeHitInterface = Cast<IBeHitInterface>(HitActor))
	{
		if (AGunplayCharacter* HitterCharacter = PickupComponent->GetOwnerCharacter())
		{
			const FHitInfo HitInfo(HitterCharacter->GetController(), HitterCharacter, Force, HitResult.Location,
			                       CalculateDamage(HitResult));

			BeHitInterface->BeHit(HitInfo);
		}
	}
	return true;
}
