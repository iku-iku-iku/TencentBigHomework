// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_LookAt.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTT_LookAt : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTT_LookAt();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual FString GetStaticDescription() const override;
};
