// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/Service/GunplayBTSBase.h"
#include "BTS_UpdateTimer.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTS_UpdateTimer : public UGunplayBTSBase
{
	GENERATED_BODY()

	UBTS_UpdateTimer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category="Enemy")
	TArray<FBlackboardKeySelector> Timers;
};