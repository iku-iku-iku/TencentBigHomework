// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/EnemySpawner.h"

#include "Character/Enemy/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Game/Solitary/ExtremeSurvivalGameMode.h"
// Sets default values
AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SpawnTimer -= DeltaSeconds;

	if (SpawnTimer < 0 && RemainingSpawnCount > 0)
	{
		RemainingSpawnCount--;
		SpawnTimer = SpawnInterval;
		SpawnEnemy();
	}
}

void AEnemySpawner::SpawnEnemy()
{
	TSubclassOf<AEnemyCharacter> EnemyClassToSpawn;
	if (EnemyClass)
	{
		EnemyClassToSpawn = EnemyClass;
	}
	else if (AExtremeSurvivalGameMode* ExtremeSurvivalGameMode = Cast<AExtremeSurvivalGameMode>(
		UGameplayStatics::GetGameMode(this)))
	{
		EnemyClassToSpawn = ExtremeSurvivalGameMode->GetRandomEnemyClass();
	}
	if (UWorld* World = GetWorld())
	{
		check(EnemyClassToSpawn != nullptr);
		const FVector Location = GetActorLocation();
		World->SpawnActor<AEnemyCharacter>(EnemyClassToSpawn, Location, FRotator(0.f));
	}
}
