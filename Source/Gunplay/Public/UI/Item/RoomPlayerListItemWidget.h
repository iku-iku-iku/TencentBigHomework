// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomPlayerListItemWidget.generated.h"

/**
 *  房间中的玩家信息Item
 */
UCLASS()
class GUNPLAY_API URoomPlayerListItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InjectPlayerInfo(const struct FPlayerInfo& PlayerInfo) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Item")
	FLinearColor HostColor;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	FLinearColor ReadyColor;
	
	UPROPERTY(EditDefaultsOnly, Category="Item")
	FLinearColor NotReadyColor;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* PlayerNameText;

	UPROPERTY(meta=(BindWidget))
	class UBorder* ReadyStatus;
};
