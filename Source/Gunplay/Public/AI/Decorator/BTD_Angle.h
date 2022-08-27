// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_Angle.generated.h"


/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTD_Angle : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UBTD_Angle();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(Category="Angle", EditAnywhere, meta=(DisplayName = "Compare Type"))
	int8 CompareType = 1;

	UPROPERTY(EditAnywhere, Category="Angle")
	float Degree;
};
