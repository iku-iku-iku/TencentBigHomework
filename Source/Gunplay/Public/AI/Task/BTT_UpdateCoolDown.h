// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_UpdateCoolDown.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTT_UpdateCoolDown : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTT_UpdateCoolDown();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category="CoolDown")
	bool bUseAttackIntervalAsCoolDown = true;

	UPROPERTY(EditAnywhere, Category="CoolDown")
	float CoolDownTime;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
};
