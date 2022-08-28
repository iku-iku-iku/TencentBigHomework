// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyCharacter;
UCLASS()
class GUNPLAY_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE void SetSpawnCount(const int32 NewValue) { RemainingSpawnCount = NewValue; }

	FORCEINLINE void SetSpawnTimer(const int32 NewValue) { SpawnTimer = NewValue; }
protected:
	UPROPERTY(EditAnywhere, Category="Enemy")
	TSubclassOf<AEnemyCharacter> EnemyClass = nullptr;

	UPROPERTY(EditAnywhere, Category="Enemy")
	int32 RemainingSpawnCount = 0;

private:
	void SpawnEnemy();

	float SpawnInterval = 5.f;

	float SpawnTimer = 0.f;
};
