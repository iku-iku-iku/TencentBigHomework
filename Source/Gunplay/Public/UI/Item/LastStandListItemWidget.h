// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfoListItemWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/Game/PlayerInfoListWidget.h"
#include "LastStandListItemWidget.generated.h"


/**
 * 排名Item
 */
UCLASS()
class GUNPLAY_API ULastStandListItemWidget : public UPlayerInfoListItemWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* LifeNum;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Rank;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Name;

private:
	UFUNCTION()
	FText GetLifeNum();

	UFUNCTION()
	FText GetPlayerName();

	UFUNCTION()
	FText GetRank();
	
	UFUNCTION()
	FSlateColor GetNameColor();
};
