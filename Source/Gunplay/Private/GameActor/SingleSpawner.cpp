// Copyright iku-iku-iku,. All Rights Reserved.


#include "GameActor/SingleSpawner.h"

#include "Components/StaticMeshComponent.h"
#include "Component/PickupComponent.h"
#include "Component/SpawnComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Util/GunplayUtils.h"

ASingleSpawner::ASingleSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("/Game/Meshes/SpawnerPillar.SpawnerPillar"));
	if (MeshFinder.Succeeded())
	{
		Mesh->SetStaticMesh(MeshFinder.Object);
	}

	bReplicates = true;
}

void ASingleSpawner::SpawnTarget()
{
	if (!HasAuthority()) return;
	
	if (UWorld* World = GetWorld())
	{
		const FVector SpawnLocation = GetActorLocation() + FVector::UpVector * SpawnHeight;
		if (const AActor* SpawnedActor = World->SpawnActor<AActor>(TargetToSpawn, SpawnLocation, FRotator(0.f)))
		{
			if (USpawnComponent* SpawnComponent = GunplayUtils::GetComponent<USpawnComponent>(SpawnedActor))
			{
				SpawnComponent->SetSpawner(this);
				if (const UPickupComponent* PickupComponent = GunplayUtils::GetComponent_Const<UPickupComponent>(
					SpawnedActor))
				{
					PickupComponent->SetPickable(true);
				}
			}
		}
	}
}

void ASingleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Empty)
	{
		SpawnTimer -= DeltaTime;
		if (SpawnTimer < 0)
		{
			SpawnTimer = SpawnInterval;
			SpawnTarget();
			Empty = false;
		}
	}
}
