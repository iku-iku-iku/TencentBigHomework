// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Stop.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTT_Stop : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_Stop();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	bool Stop(AAIController* Controller);
};
