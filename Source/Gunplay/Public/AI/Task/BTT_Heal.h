// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Heal.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTT_Heal : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_Heal();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	UPROPERTY(EditAnywhere, Category="Heal")
	float HealRatio;

	UPROPERTY(EditAnywhere, Category="Heal")
	float HealInterval;

	float LastTime;
	
	float Timer;
};
