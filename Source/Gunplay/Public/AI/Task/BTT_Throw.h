// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Character/GunplayCharacter.h"
#include "BTT_Throw.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTT_Throw : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTT_Throw();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	UPROPERTY(EditAnywhere, Category="Throw")
	TSubclassOf<class AActor> ThrowHoldingClass;

	void CreateThrowHolding(AGunplayCharacter* Receiver) const;

	bool ThrowAt(const AActor* Target, AActor* ThrowThing, class AEnemyCharacter* EnemyCharacter);

	UPROPERTY(EditAnywhere, Category="Throw")
	float LookHeightScale= 0.5f;
};
