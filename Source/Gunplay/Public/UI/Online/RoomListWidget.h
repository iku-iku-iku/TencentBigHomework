// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Item/RoomListItemWidget.h"
#include "Blueprint/UserWidget.h"
#include "RoomListWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API URoomListWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void PopulateList(const TArray<FOnlineSessionSearchResult>& SearchResults);
	
protected:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* HintText;
	
	UPROPERTY(meta=(BindWidget))
	class UScrollBox* RoomList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URoomListItemWidget> RoomListItemClass;
};
