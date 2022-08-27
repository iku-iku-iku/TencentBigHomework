#include "GameActor/Target.h"

#include "GameFramework/Character.h"
#include "Character/GunplayCharacter.h"
#include "Component/IconComponent.h"
#include "Component/SpawnComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Game/GunplayPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	SpawnComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("Spawn Component"));

	IconComponent = CreateDefaultSubobject<UIconComponent>(TEXT("Icon Component"));
	IconComponent->SetupAttachment(RootComponent);

	IconComponent->SetRelativeLocation(FVector(0, 0, 70.f));

	bReplicates = true;
	SetReplicatingMovement(true);
}

<<<<<<< HEAD
bool ATarget::CanAdsorb() const
{
	return SpawnComponent->GetSpawner() != nullptr;
}

=======
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TargetPhysics = ETargetPhysics::Init;
		OnRep_Physics();
	}
}

void ATarget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATarget, TargetPhysics)
}

void ATarget::OnRep_Physics()
{
	if (TargetPhysics == ETargetPhysics::Init)
	{
		SetInitialPhysics();
	} else if (TargetPhysics == ETargetPhysics::Hit)
	{
		SetHitPhysics();
	}
}

void ATarget::BeHitFirstTime(AGunplayPlayerController* HitterPlayer)
{
	check(HasAuthority())

	BeHitFirstTimeDelegate.Broadcast(this);

	if (IconComponent)
	{
		IconComponent->DestroyComponent();
	}

	TargetPhysics = ETargetPhysics::Hit;
	OnRep_Physics();

	if (IsValid(HitterPlayer))
	{
		EffectWhenHitBy(HitterPlayer);
	}
}

void ATarget::SetInitialPhysics() const
{
	Mesh->SetSimulatePhysics(true);
	FBodyInstance* BodyInstance = Mesh->GetBodyInstance();
	BodyInstance->bLockXRotation = 1;
	BodyInstance->bLockYRotation = 1;
	BodyInstance->bLockZRotation = 1;
	BodyInstance->bLockXTranslation = 1;
	BodyInstance->bLockYTranslation = 1;
	Mesh->SetConstraintMode(EDOFMode::SixDOF);
}

void ATarget::SetHitPhysics() const
{
	FBodyInstance* BodyInstance = Mesh->GetBodyInstance();
	BodyInstance->bLockXRotation = 0;
	BodyInstance->bLockYRotation = 0;
	BodyInstance->bLockZRotation = 0;
	BodyInstance->bLockXTranslation = 0;
	BodyInstance->bLockYTranslation = 0;
	Mesh->SetConstraintMode(EDOFMode::Default);
}

void ATarget::BeHit(const FHitInfo& HitInfo)
{
	check(HasAuthority())
	Mesh->AddImpulseAtLocation(HitInfo.Impulse, HitInfo.HitLocation);

	if (AGunplayPlayerController* PlayerHitter = Cast<AGunplayPlayerController>(HitInfo.Hitter))
	{
		// 不在Spawner上时不起效果
		if (SpawnComponent->GetSpawner())
		{
			SpawnComponent->ResetSpawner();

			BeHitFirstTime(PlayerHitter);
		}
	}
}
