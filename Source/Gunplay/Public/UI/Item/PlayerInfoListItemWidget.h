// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/Online/OnlinePlayerState.h"
#include "PlayerInfoListItemWidget.generated.h"


/**
 * 对局中的玩家的信息项
 */
UCLASS()
class GUNPLAY_API UPlayerInfoListItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FORCEINLINE void Inject(class AOnlinePlayerState* InjectState) { PlayerState = InjectState; }

protected:
	UPROPERTY()
	class AOnlinePlayerState* PlayerState;
};
