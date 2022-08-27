// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/ExplosionComponent.h"

#include "CollisionShape.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Interface/BeHitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

UExplosionComponent::UExplosionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Explosion Force"));
	RadialForceComponent->SetupAttachment(this);
	RadialForceComponent->ImpulseStrength = 2e5f;
	RadialForceComponent->Radius = 300.f;
}

void UExplosionComponent::Multi_Explode_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetOwner()->GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(this, PS_Explosion, GetOwner()->GetActorLocation());
}

void UExplosionComponent::Server_Explode_Implementation(FHitInfo InHitInfo)
{
	Multi_Explode();
	TArray<FHitResult> OutHits;
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = Start;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(RadialForceComponent->Radius);

	if (GetWorld()->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_WorldDynamic, Sphere))
	{
		TSet<AActor*> HitActors;
		for (auto& Hit : OutHits)
		{
			AActor* HitActor = Hit.GetActor();
			if (! HitActors.Contains(HitActor))
			{
				HitActors.Add(HitActor);

				if (IBeHitInterface* BeHitInterface = Cast<IBeHitInterface>(HitActor))
				{
					if (AGunplayCharacter* HitterCharacter = InHitInfo.HitterCharacter)
					{
						FVector Direction = (HitActor->GetActorLocation() - Start).GetSafeNormal();
						const FVector Impulse = Direction * RadialForceComponent->ImpulseStrength;

						InHitInfo.HitLocation = Hit.Location;
						InHitInfo.Impulse = Impulse;
						BeHitInterface->BeHit(InHitInfo);
					}
				}
			}
		}
	}
}
