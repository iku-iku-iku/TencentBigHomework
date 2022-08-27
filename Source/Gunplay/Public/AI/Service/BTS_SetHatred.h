// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GunplayBTSBase.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_SetHatred.generated.h"

/**
 * 设定仇恨
 */
UCLASS()
class GUNPLAY_API UBTS_SetHatred : public UGunplayBTSBase
{
	GENERATED_BODY()

public:
	UBTS_SetHatred();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


private:

	// 寻找仇恨对象
	class APlayerCharacter* FindHatred() const;

};
