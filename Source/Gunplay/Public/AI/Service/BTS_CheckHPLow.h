// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GunplayBTSBase.h"
#include "BTS_CheckHPLow.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTS_CheckHPLow : public UGunplayBTSBase
{
	GENERATED_BODY()

public:
	UBTS_CheckHPLow();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category="Check HP Low")
	float Threshold;
};
