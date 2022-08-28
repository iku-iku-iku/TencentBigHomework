// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GunplayCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "Manager/BleedingTextManager.h"
// #include "Containers/Map.h"
#include "Templates/Tuple.h"
#include "ExtremeSurvivalGameMode.generated.h"

DECLARE_EVENT_OneParam(AExtremeSurvivalGameMode, FOnStartNextWaveEvent, int)

/**
 * @title 极限生存玩法
 * @desc 波数无限递增，每一波有若干敌人需要被击杀，击杀所有敌人后即为通过这一波
 */
UCLASS()
class GUNPLAY_API AExtremeSurvivalGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AExtremeSurvivalGameMode();

	void OnEnemyDeath(const AGunplayCharacter* Enemy);

	UFUNCTION()
	void OnActorSpawned(AActor* SpawnedActor);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
public:
	FORCEINLINE FOnStartNextWaveEvent& OnStartNextWave() { return StartNextWaveEvent; }

	TSubclassOf<class AEnemyCharacter> GetRandomEnemyClass();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	TArray<TSubclassOf<class AEnemyCharacter>> EnemyClasses;

private:
	UPROPERTY(VisibleAnywhere, Category="Game")
	TArray<class AEnemySpawner*> EnemySpawners;

	UPROPERTY(VisibleAnywhere, Category="Game")
	int32 WaveCount;

	UPROPERTY(VisibleAnywhere, Category="Game")
	int32 RemainingEnemyCount = 0;

	typedef TTuple<TSubclassOf<class AEnemyCharacter>, float> FClass2Float;
	TArray<FClass2Float> EnemyClass2SpawnProbability;

	FOnStartNextWaveEvent StartNextWaveEvent;


private:
	void StartNextWave();

	void FillEnemySpawnProbability();

	FORCEINLINE int32 GetMaxSpawnCount() const { return WaveCount * 2; }

	// 距离下一波的间隔（留给玩家的补给时间）
	FORCEINLINE int32 GetWaveInterval() const { return 5.f; }
};
