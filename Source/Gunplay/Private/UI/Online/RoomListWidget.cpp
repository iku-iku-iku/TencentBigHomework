// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Online/RoomListWidget.h"
#include "Components/TextBlock.h"
#include "OnlineSessionSettings.h"
#include "Components/ScrollBox.h"
#include "UI/Item/RoomListItemWidget.h"

void URoomListWidget::PopulateList(const TArray<FOnlineSessionSearchResult>& SearchResults)
{
	RoomList->ClearChildren();
	HintText->SetText(FText::FromString(FString::Printf(TEXT("找到%d个房间"), SearchResults.Num())));
	for (const FOnlineSessionSearchResult& SearchResult : SearchResults)
	{
		if (URoomListItemWidget* RoomListItemWidget = CreateWidget<URoomListItemWidget>(this, RoomListItemClass))
		{
			RoomListItemWidget->Inject(SearchResult);
			RoomList->AddChild(RoomListItemWidget);
		}
	}
}
