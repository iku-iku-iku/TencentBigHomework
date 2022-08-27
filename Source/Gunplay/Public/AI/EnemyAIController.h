// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Character/GunplayCharacter.h"
#include "EnemyAIController.generated.h"

/**
 * 敌人的AI控制器
 */
UCLASS()
class GUNPLAY_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnAIDeath(const AGunplayCharacter*GunplayCharacter);

public:
	FORCEINLINE void SetAttackInterval(const float NewValue)
	{
		AttackInterval = NewValue;
	}

	FORCEINLINE void SetAttackDuration(const float NewValue)
	{
		AttackDuration = NewValue;
	}

	FORCEINLINE float GetAttackInterval() const
	{
		return AttackInterval;
	}

	FORCEINLINE float GetAttackDuration() const
	{
		return AttackDuration;
	}

protected:
	// AI的攻击间隔
	UPROPERTY(EditAnywhere, Category="Enemy")
	float AttackInterval = 1.f;

	// AI一次攻击的持续时间
	UPROPERTY(EditAnywhere, Category="Enemy")
	float AttackDuration = 0.2f;
};
