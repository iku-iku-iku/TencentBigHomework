// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Item/RoomListItemWidget.h"
#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GunplayGameInstance.h"
#include "UI/Util/LoadingWidget.h"

void URoomListItemWidget::NativeOnInitialized()
{
	Super::NativeConstruct();

	JoinBtn->OnClicked.AddDynamic(this, &URoomListItemWidget::JoinRoom);
}

void URoomListItemWidget::Inject(const FOnlineSessionSearchResult& SearchResult)
{
	OnlineSessionSearchResult = SearchResult;
	if (SearchResult.IsValid() && ServerNameText && PingText && PlayerNumText)
	{
		ServerNameText->SetText(FText::FromString(SearchResult.Session.OwningUserName));
		PingText->SetText(FText::FromString(FString::FromInt(SearchResult.PingInMs)));
		const int32 CurrentPlayers = SearchResult.Session.SessionSettings.NumPublicConnections - SearchResult.Session.
			NumOpenPublicConnections;
		const int32 MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
		PlayerNumText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentPlayers, MaxPlayers)));
	}
}

void URoomListItemWidget::JoinRoom()
{
	if (UGunplayGameInstance* OnlineGameInstance = Cast<UGunplayGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		OnlineGameInstance->JoinSession(GetOwningLocalPlayer(), OnlineSessionSearchResult);

		if (ULoadingWidget* LoadingWidget = CreateWidget<ULoadingWidget>(this, LoadingWidgetClass))
		{
			LoadingWidget->InjectMessage(TEXT("正在加入房间"));
			LoadingWidget->AddToViewport();
		}
	}
}
