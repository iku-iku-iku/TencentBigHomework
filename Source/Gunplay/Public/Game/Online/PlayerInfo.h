// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"

/**
 * 玩家信息
 */
USTRUCT(BlueprintType)
struct GUNPLAY_API FPlayerInfo 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FText PlayerName{};

	UPROPERTY()
	bool bIsReady = false;

	UPROPERTY()
	bool bIsHost = false;
};
