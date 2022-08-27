// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/Service/GunplayBTSBase.h"
#include "BTS_SetStatus.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTS_SetStatus : public UGunplayBTSBase
{
	GENERATED_BODY()

	UBTS_SetStatus();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
