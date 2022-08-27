#include "Holding/Grenade.h"

#include "TimerManager.h"
<<<<<<< HEAD
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/CharacterStatusComponent.h"
#include "Character/GunplayCharacter.h"
#include "Component/ExplosionComponent.h"
#include "Component/PickupComponent.h"
#include "Component/ProjectileComponent.h"
=======
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Component/CharacterStatusComponent.h"
#include "Character/GunplayCharacter.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Component/PickupComponent.h"
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
#include "Component/SpawnComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
<<<<<<< HEAD
=======
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Sound/SoundCue.h"
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
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

<<<<<<< HEAD
=======
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Explosion Force"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->ImpulseStrength = 2e5f;
	RadialForceComponent->Radius = 300.f;


>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
	// set default mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GrenadesFinder(TEXT("/Game/Weapons/Grenade.Grenade"));
	if (GrenadesFinder.Succeeded())
	{
		Mesh->SetStaticMesh(GrenadesFinder.Object);
		Mesh->SetSimulatePhysics(false);
	}

<<<<<<< HEAD
	SpawnComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("Spawn Component"));

	ProjectileComponent = CreateDefaultSubobject<UProjectileComponent>(TEXT("Projectile Component"));

	ExplosionComponent = CreateDefaultSubobject<UExplosionComponent>(TEXT("Explosion Component"));
=======
	// set default particle
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PSFinder(
		TEXT("/Game/ParticleSystem/P_Explosion.P_Explosion"));
	if (PSFinder.Succeeded())
	{
		PS_Explosion = PSFinder.Object;
	}

	// set default sound
	static ConstructorHelpers::FObjectFinder<USoundCue> SoundFinder(
		TEXT("/Game/Sounds/Impacts/SC_GrenadeExplosion.SC_GrenadeExplosion"));
	if (SoundFinder.Succeeded())
	{
		ExplosionSound = SoundFinder.Object;
	}

	SpawnComponent = CreateDefaultSubobject<USpawnComponent>(TEXT("Spawn Component"));

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

void AGrenade::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
}

void AGrenade::BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter)
{
	Super::BeObtainedBy_Implementation(GunplayCharacter);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (HasAuthority())
	{
		PickupComponent->AttachToPlayer(GunplayCharacter);

		SpawnComponent->ResetSpawner();
<<<<<<< HEAD
=======
		if (ParticleSystemComponent) { ParticleSystemComponent->DestroyComponent(); }
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
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
<<<<<<< HEAD
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
=======
	if (const ACharacter* OwnerPlayer = PickupComponent->GetOwnerCharacter())
	{
		if (const USkeletalMeshComponent* SkeletalMeshComponent = OwnerPlayer->GetMesh())
		{
			if (UAnimInstance* AnimInst = SkeletalMeshComponent->GetAnimInstance())
			{
				if (bStart)
				{
					if (! AnimInst->Montage_IsPlaying(Montage_ThrowGrenade))
					{
						UE_LOG(LogTemp, Warning, TEXT("Start Montage"))

						AnimInst->Montage_Play(Montage_ThrowGrenade);
					}
				}
				else
				{
					if (AnimInst->Montage_IsPlaying(Montage_ThrowGrenade) &&
						! AnimInst->Montage_GetCurrentSection(Montage_ThrowGrenade).IsEqual(TEXT("ThrowEnd")))
					{
						UE_LOG(LogTemp, Warning, TEXT("End Montage"))

						AnimInst->Montage_JumpToSection(TEXT("ThrowEnd"), Montage_ThrowGrenade);
					}
				}
			}
		}
	}
	// 使用动画通知在投掷动画结束时投掷
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
}

void AGrenade::Server_ThrowMontage_Implementation(bool bStart)
{
	Multi_ThrowMontage(bStart);
}

void AGrenade::ThrowGrenade()
{
	Server_ThrowGrenade();
}

<<<<<<< HEAD
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
=======
void AGrenade::Server_ThrowGrenade_Implementation()
{
	if (bHasBeenThrown) { return; }
	bHasBeenThrown = true;
	
	if (const AGunplayCharacter* OwnerCharacter = PickupComponent->GetOwnerCharacter())
	{
		FVector Forward;
		if (const UCameraComponent* CameraComponent = Cast<UCameraComponent>(
			OwnerCharacter->GetComponentByClass(UCameraComponent::StaticClass())))
		{
			Forward = CameraComponent->GetForwardVector();
		}
		else
		{
			const AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerCharacter);
			check(EnemyCharacter != nullptr)

			Forward = EnemyCharacter->GetAttackForward();
		}

		const FVector ThrowDirection = (Forward + FVector::UpVector * ThrowHeightScale).GetSafeNormal();

		PickupComponent->DetachFromPlayer();
		PickupComponent->SetPickable(false);

		SetActorLocation(GetActorLocation() + ThrowDirection * ThrowStartOffset);
		Mesh->AddImpulse(ThrowDirection * BaseThrowForce);

		GetWorld()->GetTimerManager().SetTimer(Server_TimerHandleExplode, this, &AGrenade::Explode,
		                                       ExplodeDelayTime,
		                                       false);
	}
}

void AGrenade::Multi_Explode_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PS_Explosion, GetActorLocation());
}

void AGrenade::Explode_Implementation()
{
	Multi_Explode();
	TArray<FHitResult> OutHits;
	const FVector Start = GetActorLocation();
	const FVector End = Start;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(RadialForceComponent->Radius);
	if (GetWorld()->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_WorldDynamic, Sphere))
	{
		for (auto& Hit : OutHits)
		{
			AActor* HitActor = Hit.GetActor();
			if (IBeHitInterface* BeHitInterface = Cast<IBeHitInterface>(HitActor))
			{
				if (AGunplayCharacter* HitterCharacter = PickupComponent->GetOwnerCharacter())
				{
					FVector Direction = (HitActor->GetActorLocation() - Start).GetSafeNormal();
					const FVector Impulse = Direction * RadialForceComponent->ImpulseStrength;

					const FHitInfo HitInfo(HitterCharacter->GetController(), HitterCharacter, Impulse, Hit.Location,
					                       DamageScale * PickupComponent->GetOwnerCharacter()->GetStatus()->
					                                                      GetAttack());
					BeHitInterface->BeHit(HitInfo);
				}
			}
		}
	}

	Destroy();
}
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
