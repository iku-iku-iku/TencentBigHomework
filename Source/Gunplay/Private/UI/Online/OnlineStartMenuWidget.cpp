// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Online/OnlineStartMenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GunplayGameInstance.h"
#include "UI/Util/LoadingWidget.h"
#include "UI/Online/RoomListWidget.h"

void UOnlineStartMenuWidget::NativeOnInitialized()
{
	Super::NativeConstruct();

	CreateRoomBtn->OnClicked.AddDynamic(this, &UOnlineStartMenuWidget::CreateRoom);
	SearchRoomBtn->OnClicked.AddDynamic(this, &UOnlineStartMenuWidget::SearchRoom);
	SettingBtn->OnClicked.AddDynamic(this, &UOnlineStartMenuWidget::Setting);
	ExitBtn->OnClicked.AddDynamic(this, &UOnlineStartMenuWidget::Exit);


	if (UGunplayGameInstance* OnlineGameInstance = Cast<UGunplayGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		OnlineGameInstance->OnFindSessionComplete().AddUObject(this, &UOnlineStartMenuWidget::OnFindSessionComplete);
		OnlineGameInstance->OnCreateSessionComplete().
		                    AddUObject(this, &UOnlineStartMenuWidget::OnCreateSessionComplete);
	}
}

void UOnlineStartMenuWidget::Exit()
{
	UGameplayStatics::OpenLevel(this, GunplayStartLevelName);
}

void UOnlineStartMenuWidget::Setting()
{
	if (WidgetSwitcher)
	{
		WidgetSwitcher->SetActiveWidgetIndex(2);
	}
}

void UOnlineStartMenuWidget::CreateRoom()
{
	if (CheckNameSet())
	{
		WidgetSwitcher->SetActiveWidgetIndex(0);
		if (UGunplayGameInstance* OnlineGameInstance = Cast<
			UGunplayGameInstance>(UGameplayStatics::GetGameInstance(this)))
		{
			OnlineGameInstance->CreateSession(4);

			LoadingWidget = OnlineGameInstance->ShowLoading(TEXT("正在创建房间"));
		}
	}
}

void UOnlineStartMenuWidget::SearchRoom()
{
	if (CheckNameSet())
	{
		WidgetSwitcher->SetActiveWidgetIndex(1);
		if (UGunplayGameInstance* OnlineGameInstance = Cast<
			UGunplayGameInstance>(UGameplayStatics::GetGameInstance(this)))
		{
			OnlineGameInstance->SearchSession();

			LoadingWidget = OnlineGameInstance->ShowLoading(TEXT("正在搜索房间"));
		}
	}
}

bool UOnlineStartMenuWidget::CheckNameSet() const
{
	if (UGunplayGameInstance* OnlineGameInstance = Cast<UGunplayGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		if (UGunplayGameInstance::GetInstance()->GetPlayerName().EqualTo(FText::FromString(TEXT(""))))
		{
			OnlineGameInstance->ShowMessage(FText::FromString(TEXT("请先设置名称")));
			return false;
		}
		return true;
	}
	return false;
}

void UOnlineStartMenuWidget::OnCreateSessionComplete(bool bWasSuccessful)
{
	if (LoadingWidget)
	{
		LoadingWidget->RemoveFromParent();
	}
}

void UOnlineStartMenuWidget::OnFindSessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (const UGunplayGameInstance* OnlineGameInstance = Cast<
			UGunplayGameInstance>(UGameplayStatics::GetGameInstance(this)))
		{
			UE_LOG(LogTemp, Warning, TEXT("Populated with %d results"), OnlineGameInstance->GetSearchResults().Num())

			RoomList->PopulateList(OnlineGameInstance->GetSearchResults());
		}
	}
	if (LoadingWidget)
	{
		LoadingWidget->RemoveFromParent();
	}
}
