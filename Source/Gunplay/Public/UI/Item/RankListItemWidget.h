// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/Online/OnlinePlayerState.h"
#include "RankListItemWidget.generated.h"


/**
 * 排名Item
 */
UCLASS()
class GUNPLAY_API URankListItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FORCEINLINE void Inject(class AOnlinePlayerState* InjectState) { PlayerState = InjectState; }
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Score;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Rank;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Name;

private:
	UPROPERTY()
	class AOnlinePlayerState* PlayerState;

	UFUNCTION()
	FText GetScore();

	UFUNCTION()
	FText GetPlayerName();

	UFUNCTION()
	FText GetRank();
	
	UFUNCTION()
	FSlateColor GetNameColor();
};
