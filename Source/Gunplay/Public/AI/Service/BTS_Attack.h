// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GunplayBTSBase.h"
#include "BTS_Attack.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTS_Attack : public UGunplayBTSBase
{
	GENERATED_BODY()


	UBTS_Attack();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void Attack();

	void SetInterval();
	
	UFUNCTION()
	void FinishAttack() const;

	UPROPERTY(EditAnywhere, Category="Attack")
	float OneAttackDuration;
};
