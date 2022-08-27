// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "SmartEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API ASmartEnemy : public AEnemyCharacter
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

public:
	virtual float GetSpawnProbabilityWithoutDeviation(int32 WaveCount) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<class AHands> HandClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<class AGun> GunClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<class AGrenade> GrenadeClass;
};
