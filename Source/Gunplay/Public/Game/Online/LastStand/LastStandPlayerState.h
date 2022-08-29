// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/Online/OnlinePlayerState.h"
#include "LastStandPlayerState.generated.h"


UCLASS()
class GUNPLAY_API ALastStandPlayerState : public AOnlinePlayerState
{
	GENERATED_BODY()

public:
	FORCEINLINE int32 GetLifeNum() const { return LifeNum; }

	FORCEINLINE void SetLifeNum(const int32 NewValue) { LifeNum = NewValue; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing=OnRep_LifeNum, BlueprintReadOnly, Category=PlayerState)
	int32 LifeNum;

	UFUNCTION()
	void OnRep_LifeNum();
};
