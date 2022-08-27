// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "GunplayBTSBase.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UGunplayBTSBase : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UGunplayBTSBase();
	
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	
	UPROPERTY()
	class AGunplayCharacter* ControlledCharacter;

	UPROPERTY()
	class AAIController* Controller;

	UPROPERTY()
	class UBlackboardComponent* Blackboard;
};
