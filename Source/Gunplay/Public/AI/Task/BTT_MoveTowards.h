// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_MoveTowards.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTT_MoveTowards : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTT_MoveTowards();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	UPROPERTY(EditAnywhere, Category="Move")
	float Speed = 700.f;

	virtual FString GetStaticDescription() const override;
};
