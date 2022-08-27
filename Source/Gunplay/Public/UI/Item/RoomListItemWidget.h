// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "Blueprint/UserWidget.h"
#include "RoomListItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API URoomListItemWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
protected:
	UPROPERTY(EditDefaultsOnly, Category="Online")
	TSubclassOf<class ULoadingWidget> LoadingWidgetClass;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ServerNameText;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* PingText;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* PlayerNumText;

	UPROPERTY(meta=(BindWidget))
	class UButton* JoinBtn;
public:
	void Inject(const FOnlineSessionSearchResult& SearchResult);

private:
	UFUNCTION()
	void JoinRoom();

	FOnlineSessionSearchResult OnlineSessionSearchResult;
};
