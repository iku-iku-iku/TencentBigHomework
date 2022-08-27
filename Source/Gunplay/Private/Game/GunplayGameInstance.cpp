// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/GunplayGameInstance.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/Util/MessageWidget.h"
#include "OnlineSubsystemUtils.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/BleedingTextManager.h"
#include "UI/Util/LoadingWidget.h"
#include "UI/Util/DialogWidget.h"

UGunplayGameInstance::UGunplayGameInstance()
{
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(
		this, &UGunplayGameInstance::OnCreateSessionComplete);

	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(
		this, &UGunplayGameInstance::OnJoinSessionComplete);

	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(
		this, &UGunplayGameInstance::OnFindSessionComplete);

	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(
		this, &UGunplayGameInstance::OnStartSessionComplete);

	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(
		this, &UGunplayGameInstance::OnDestroySessionComplete);
}

void UGunplayGameInstance::Init()
{
	Super::Init();

	bIsDSInstance = IsDedicatedServerInstance();
	// 初始化BleedingTextManager
	if (!bIsDSInstance)
	{
		if (BleedingTextManagerClass)
		{
			UE_LOG(LogEffect, Warning, TEXT("Init Bleeding Text Manager"))

			if (UBleedingTextManager* BleedingTextManager = NewObject<UBleedingTextManager>(
				this, BleedingTextManagerClass, TEXT("Bleeding Text Manager")))
			{
				AddSingletonInternal(UBleedingTextManager::StaticClass(), BleedingTextManager);
			}
		}
	}
	else
	{
		UE_LOG(LogDS, Warning, TEXT("DS Instance Init"))

		ResetDSLevel();
	}
}


void UGunplayGameInstance::ResetDSLevel()
{
	DS_MatchPlayerUniqueNetIds.Empty();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]
	{
		UGameplayStatics::OpenLevel(this, DSLevelName, true, TEXT("listen"));

		UE_LOG(LogDS, Warning, TEXT("重置了DS所在的Level为 %s"), *DSLevelName.ToString());
	}, 0.5f, false);
}

UGunplayGameInstance* UGunplayGameInstance::GetInstance()
{
	if (GEngine)
	{
		if (const FWorldContext* WorldContextFromGameViewport = GEngine->GetWorldContextFromGameViewport(
			GEngine->GameViewport))
		{
			return Cast<UGunplayGameInstance>(WorldContextFromGameViewport->OwningGameInstance);
		}
	}
	return nullptr;
}

const FText& UGunplayGameInstance::GetPlayerName()
{
	return PlayerName;
}

void UGunplayGameInstance::ShowMessage(const FText Message)
{
	if (MessageWidgetClass)
	{
		if (UMessageWidget* MessageWidget = CreateWidget<UMessageWidget>(this, MessageWidgetClass))
		{
			MessageWidget->InjectMessage(Message);
			MessageWidget->AddToViewport();
		}
	}
}

ULoadingWidget* UGunplayGameInstance::ShowLoading(const FString& Message)
{
	if (LoadingWidgetClass)
	{
		if (ULoadingWidget* LoadingWidget = CreateWidget<ULoadingWidget>(this, LoadingWidgetClass))
		{
			LoadingWidget->InjectMessage(Message);
			LoadingWidget->AddToViewport();
			return LoadingWidget;
		}
	}
	return nullptr;
}

UDialogWidget* UGunplayGameInstance::ShowDialog()
{
	if (DialogWidgetClass)
	{
		if (UDialogWidget* DialogWidget = CreateWidget<UDialogWidget>(this, DialogWidgetClass))
		{
			DialogWidget->AddToViewport();
			return DialogWidget;
		}
	}
	return nullptr;
}

void UGunplayGameInstance::CreateSession(int32 ConnNum)
{
	MaxPlayerNum = ConnNum;

	if (GetLocalPlayers().Num() != 0)
	{
		UserId = (*GetLocalPlayers()[0]->GetPreferredUniqueNetId()).AsShared();

		if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
		{
			UE_LOG(LogTemp, Warning, TEXT("使用联网子系统: %s"), *OnlineSubsystem->GetSubsystemName().ToString())

			const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();

			if (OnlineSessionPtr.IsValid() && UserId.IsValid())
			{
				FOnlineSessionSettings Settings;
				Settings.NumPublicConnections = ConnNum;
				Settings.NumPrivateConnections = 0;
				// Settings.bIsDedicated = false;
				Settings.bShouldAdvertise = true;
				Settings.bIsLANMatch = bIsLAN;
				Settings.bAllowInvites = true;
				Settings.bAllowJoinInProgress = true;
				Settings.bAllowJoinViaPresence = true;
				Settings.bAllowJoinViaPresenceFriendsOnly = false;


				OnCreateSessionCompleteDelegateHandle = OnlineSessionPtr->AddOnCreateSessionCompleteDelegate_Handle(
					OnCreateSessionCompleteDelegate);

				OnlineSessionPtr->CreateSession(*UserId, NAME_GameSession, Settings);
			}
		}
	}
}

void UGunplayGameInstance::SearchSession()
{
	if (GetLocalPlayers().Num() != 0)
	{
		UserId = (*GetLocalPlayers()[0]->GetPreferredUniqueNetId()).AsShared();

		if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
		{
			UE_LOG(LogNet, Warning, TEXT("使用联网子系统: %s"), *OnlineSubsystem->GetSubsystemName().ToString())

			const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
			if (OnlineSessionPtr.IsValid() && UserId.IsValid())
			{
				SessionSearch = MakeShareable<FOnlineSessionSearch>(new FOnlineSessionSearch());
				SessionSearch->MaxSearchResults = 200000;
				SessionSearch->bIsLanQuery = bIsLAN;

				OnFindSessionCompleteDelegateHandle = OnlineSessionPtr->AddOnFindSessionsCompleteDelegate_Handle(
					OnFindSessionsCompleteDelegate);
				OnlineSessionPtr->FindSessions(*UserId, SessionSearch.ToSharedRef());
			}
		}
	}
}

bool UGunplayGameInstance::JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult)
{
	bool bWasSuccessful = false;
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem && GetLocalPlayers().Num() != 0)
	{
		UserId = LocalPlayer->GetPreferredUniqueNetId()->AsShared();
		const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
		if (UserId.IsValid() && OnlineSessionPtr.IsValid())
		{
			OnJoinSessionCompleteDelegateHandle = OnlineSessionPtr->AddOnJoinSessionCompleteDelegate_Handle(
				OnJoinSessionCompleteDelegate);
			bWasSuccessful = OnlineSessionPtr->JoinSession(*UserId, NAME_GameSession, SearchResult);
		}
	}
	return bWasSuccessful;
}

void UGunplayGameInstance::DestroySession()
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem && GetLocalPlayers().Num() != 0)
	{
		UserId = (*GetLocalPlayers()[0]->GetPreferredUniqueNetId()).AsShared();
		const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
		if (UserId.IsValid() && OnlineSessionPtr.IsValid())
		{
			OnDestroySessionCompleteDelegateHandle = OnlineSessionPtr->AddOnDestroySessionCompleteDelegate_Handle(
				OnDestroySessionCompleteDelegate);
			OnlineSessionPtr->DestroySession(CurrentSessionName);
		}
	}
}


void UGunplayGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	CreateSessionCompleteEvent.Broadcast(bWasSuccessful);
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
		OnlineSessionPtr->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);

		if (bWasSuccessful)
		{
			OnStartSessionCompleteDelegateHandle = OnlineSessionPtr->AddOnStartSessionCompleteDelegate_Handle(
				OnStartSessionCompleteDelegate);
			CurrentSessionName = SessionName;
			OnlineSessionPtr->StartSession(SessionName);
		}
		else
		{
			ShowMessage(FText::FromString(TEXT("创建房间失败")));
		}
		// if (LoadingWidget)
		// {
		// 	LoadingWidget->RemoveFromParent();
		// }
	}
}

void UGunplayGameInstance::OnJoinSessionComplete(FName SessionName, const EOnJoinSessionCompleteResult::Type Result)
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
		OnlineSessionPtr->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);

		if (Result != EOnJoinSessionCompleteResult::Success)
		{
			ShowMessage(FText::FromString(TEXT("加入房间失败")));
		}
		else
		{
			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
			{
				FString JoinAddress = "";
				OnlineSessionPtr->GetResolvedConnectString(SessionName, JoinAddress);
				if (JoinAddress != "")
				{
					CurrentSessionName = SessionName;
					PlayerController->ClientTravel(JoinAddress, TRAVEL_Absolute);
					UE_LOG(LogTemp, Warning, TEXT("成功加入会话 %s"), *SessionName.ToString())
				}
			}
		}
	}
}

void UGunplayGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
		OnlineSessionPtr->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionCompleteDelegateHandle);

		FindSessionCompleteEvent.Broadcast(bWasSuccessful);
	}
}

void UGunplayGameInstance::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
		if (OnlineSessionPtr.IsValid())
		{
			OnlineSessionPtr->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}

		if (bWasSuccessful)
		{
			UGameplayStatics::OpenLevel(this, "Room", true, "listen");
		}
	}
}

void UGunplayGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		const IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystem->GetSessionInterface();
		if (OnlineSessionPtr.IsValid())
		{
			OnlineSessionPtr->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
			// DestroySessionCompleteEvent.Broadcast(bWasSuccessful);

			if (bWasSuccessful)
			{
				UE_LOG(LogTemp, Warning, TEXT("成功销毁会话 %s"), *SessionName.ToString())
			}
		}
	}
}

void UGunplayGameInstance::AddSingleton(UClass* Class, UObject* Object)
{
	GetInstance()->AddSingletonInternal(Class, Object);
}

void UGunplayGameInstance::AddSingletonInternal(UClass* Class, UObject* Object)
{
	SingletonMap.Add(Class, Object);
}

UObject* UGunplayGameInstance::GetSingleton(const UClass* Class) const
{
	UObject** ObjectPtr = GetInstance()->SingletonMap.Find(Class);
	UObject* Ret = ObjectPtr ? *ObjectPtr : nullptr;

	if (Ret == nullptr) // 不能直接找到则试图找子类
	{
		for (const auto& Item : GetInstance()->SingletonMap)
		{
			if (Item.Key->IsChildOf(Class))
			{
				Ret = Item.Value;
				break;
			}
		}
	}

	return IsValid(Ret) ? Ret : nullptr;
}
