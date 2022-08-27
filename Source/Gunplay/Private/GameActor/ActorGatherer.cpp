// Copyright iku-iku-iku,. All Rights Reserved.


#include "GameActor/ActorGatherer.h"

#include "Components/SphereComponent.h"


AActorGatherer::AActorGatherer()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereVolume = CreateDefaultSubobject<USphereComponent>(TEXT("SphereVolume"));

	RootComponent = SphereVolume;
}

void AActorGatherer::BeginPlay()
{
	Super::BeginPlay();

	SphereVolume->OnComponentBeginOverlap.AddDynamic(this, &AActorGatherer::OnVolumeBeginOverlap);
}

void AActorGatherer::OnVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(TargetActorClass))
	{
		ProcessNewGatheredActor(OtherActor);
	}
}

void AActorGatherer::UpdateGatheredActors()
{
	GatheredActors.Reset();

	SphereVolume->GetOverlappingActors(GatheredActors, TargetActorClass);
}
