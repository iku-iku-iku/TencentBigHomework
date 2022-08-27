// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/GunEnemy.h"
#include "SlyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API ASlyEnemy : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual float GetSpawnProbabilityWithoutDeviation(int32 WaveCount) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<class AGun> GunClass;
};
