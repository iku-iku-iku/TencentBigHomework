// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "SneakEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API ASneakEnemy : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual float GetSpawnProbabilityWithoutDeviation(int32 WaveCount) override;

	virtual void BeHit(const FHitInfo& HitInfo) override;

protected:
	UPROPERTY(EditAnywhere, Category="Enemy")
	float RevealDurationWhenHit = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<class AHands> HandClass;

	// 潜行：只能被手电筒照出影子
	UFUNCTION()
	void Sneak() const;

	FTimerHandle SneakTimer;

	// 现形
	void Reveal() const;
};
