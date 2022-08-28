// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/GunplayCharacter.h"
#include "EnemyCharacter.generated.h"


/**
 * 敌人角色
 */
UCLASS()
class GUNPLAY_API AEnemyCharacter : public AGunplayCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual EGunplayCharacterType GetType() const override { return EGunplayCharacterType::Enemy; }

	virtual void BeginPlay() override;

	FORCEINLINE float GetSpawnProbability(int32 WaveCount)
	{
		return GetSpawnProbabilityWithoutDeviation(WaveCount) *
			(1 + FMath::FRandRange(-SpawnProbabilityDeviation, SpawnProbabilityDeviation));
	}

	virtual float GetSpawnProbabilityWithoutDeviation(int32 WaveCount) { return 1; }

	// 看向的方向即为攻击的方向
	void LookAt(const FVector& TargetLocation);

	FVector GetAttackForward() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	float SpawnProbabilityDeviation = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	UBehaviorTree* BehaviorTree;

	// 指示攻击的方向，如开火方向、投掷方向
	UPROPERTY()
	UArrowComponent* AttackForwardArrowComponent;
};
