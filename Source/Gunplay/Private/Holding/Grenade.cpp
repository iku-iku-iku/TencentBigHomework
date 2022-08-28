#include "Holding/Grenade.h"

#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/CharacterStatusComponent.h"
#include "Character/GunplayCharacter.h"
#include "Component/ExplosionComponent.h"
#include "Component/PickupComponent.h"
#include "Component/ProjectileComponent.h"
#include "Component/SpawnComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AGrenade::AGrenade()
{
	bReplicates = true;
	SetReplicatingMovement(true);
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetIsReplicated(true);
	RootComponent = Mesh;

	PickupComponent = CreateDefaultSubobject<UPickupComponent>(TEXT("Pickup"));
	PickupComponent->SetSocketName(AttachedSocketName);
	PickupComponent->SetupAttachment(RootComponent);

	// set default mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GrenadesFinder(TEXT("/Game/Weapons/Grenade.Grenade"));
	if (GrenadesFinder.Succeeded())
	{
		Mesh->SetStaticMesh(GrenadesFinder.Object);
		Mesh->SetSimulatePhysics(false);
	}

	SpawnComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("Spawn Component"));

	ProjectileComponent = CreateDefaultSubobject<UProjectileComponent>(TEXT("Projectile Component"));

	ExplosionComponent = CreateDefaultSubobject<UExplosionComponent>(TEXT("Explosion Component"));
}

void AGrenade::BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter)
{
	Super::BeObtainedBy_Implementation(GunplayCharacter);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (HasAuthority())
	{
		PickupComponent->AttachToPlayer(GunplayCharacter);

		SpawnComponent->ResetSpawner();
	}
}

void AGrenade::Use()
{
	Server_ThrowMontage(true);
}

void AGrenade::Using(float DeltaTime)
{
}

void AGrenade::Used()
{
	Server_ThrowMontage(false);
}


void AGrenade::Multi_ThrowMontage_Implementation(bool bStart)
{
	if (const AGunplayCharacter* OwnerCharacter = PickupComponent->GetOwnerCharacter())
	{
		if (bStart)
		{
			ProjectileComponent->Montage_StartProject(OwnerCharacter);
		}
		else
		{
			ProjectileComponent->Montage_EndProject(OwnerCharacter);
		}
	}
}

void AGrenade::Server_ThrowMontage_Implementation(bool bStart)
{
	Multi_ThrowMontage(bStart);
}

void AGrenade::ThrowGrenade()
{
	Server_ThrowGrenade();
}

void AGrenade::Server_Explode_Implementation()
{
	const float Damage = DamageScale * PickupComponent->GetOwnerCharacter()->GetStatus()->GetAttack();

	FHitInfo HitInfo;
	HitInfo.HitterCharacter = PickupComponent->GetOwnerCharacter();
	HitInfo.Hitter = HitInfo.HitterCharacter->Controller;
	HitInfo.Damage = Damage;

	ExplosionComponent->Server_Explode(HitInfo);

	Destroy();
}

void AGrenade::Server_ThrowGrenade_Implementation()
{
	if (const AGunplayCharacter* Projector = PickupComponent->GetOwnerCharacter())
	{
		PickupComponent->SetPickable(false);
		PickupComponent->DetachFromPlayer();
		ProjectileComponent->Project(Projector);

		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &AGrenade::Server_Explode, ExplodeDelayTime, false);
	}
}
