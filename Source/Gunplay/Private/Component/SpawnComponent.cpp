// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/SpawnComponent.h"

#include "Components/ShapeComponent.h"
#include "GameActor/SingleSpawner.h"

USpawnComponent::USpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpawnComponent::ResetSpawner()
{
	if (Spawner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reset Spawner"))

		Spawner->SetEmpty();
		Spawner = nullptr;
	}
}
