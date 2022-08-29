// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/Online/OnlinePlayerState.h"
#include "GameFramework/PlayerState.h"
#include "ScorePlayerState.generated.h"


UCLASS()
class GUNPLAY_API AScorePlayerState : public AOnlinePlayerState
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="State")
	void SetScore(const int32 NewValue);

	UFUNCTION(BlueprintCallable, Category="State")
	void AddScore(const int32 Delta);
};
