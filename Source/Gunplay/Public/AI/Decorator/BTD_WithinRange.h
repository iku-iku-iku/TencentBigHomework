// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_WithinRange.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTD_WithinRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UBTD_WithinRange();

	UPROPERTY(EditAnywhere, Category="WithinRange")
	float Min;
	
	UPROPERTY(EditAnywhere, Category="WithinRange")
	float Max;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
};
