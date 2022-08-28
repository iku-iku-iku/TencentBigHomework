// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ObtainHolding.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTT_ObtainHolding : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_ObtainHolding();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	UPROPERTY(EditAnywhere, Category="Holding")
	TSubclassOf<AActor> HoldingClass;
};
