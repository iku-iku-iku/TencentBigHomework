// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_CanSeeTarget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTD_CanSeeTarget : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UBTD_CanSeeTarget();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:
	UPROPERTY(EditAnywhere, Category="See")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Camera;
};
