// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Character/GunplayCharacter.h"
#include "GunEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API AGunEnemy : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual float GetSpawnProbabilityWithoutDeviation(int32 WaveCount) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<class AGun> GunClass;
};
