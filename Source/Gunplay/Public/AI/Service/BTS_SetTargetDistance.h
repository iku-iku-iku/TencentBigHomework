// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GunplayBTSBase.h"
#include "BTS_SetTargetDistance.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTS_SetTargetDistance : public UGunplayBTSBase
{
	GENERATED_BODY()

	UBTS_SetTargetDistance();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category=Blackboard)
	struct FBlackboardKeySelector TargetKey;
};
