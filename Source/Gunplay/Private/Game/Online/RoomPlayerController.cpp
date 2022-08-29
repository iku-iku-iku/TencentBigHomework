// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/RoomPlayerController.h"
#include "Game/Online/RoomGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GunplayGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "UI/Util/LoadingWidget.h"
#include "UI/Online/RoomWidget.h"

void ARoomPlayerController::Client_UpdatePlayerList_Implementation(const TArray<FPlayerInfo>& PlayerInfos)
{
	if (RoomWidget)
	{
		RoomWidget->UpdatePlayerList(PlayerInfos);
	}
}

void ARoomPlayerController::Client_StartingGame_Implementation()
{
	UGunplayGameInstance::GetInstance()->ShowLoading(TEXT("即将开始游戏"));
}

void ARoomPlayerController::Client_CreateRoomWidget_Implementation()
{
	if (RoomWidgetClass)
	{
		RoomWidget = CreateWidget<URoomWidget>(this, RoomWidgetClass);

		if (RoomWidget)
		{
			RoomWidget->AddToViewport();
		}
	}
}

void ARoomPlayerController::Server_SetPlayerInfo_Implementation(const FPlayerInfo& NewValue)
{
	PlayerInfo = NewValue;
}

void ARoomPlayerController::Client_FillPlayerInfo_Implementation()
{
	if (UGunplayGameInstance* GunplayGameInstance = UGunplayGameInstance::GetInstance())
	{
		PlayerInfo.PlayerName = GunplayGameInstance->GetPlayerName();
	}
	PlayerInfo.bIsHost = bIsHost;

	Server_SetPlayerInfo(PlayerInfo);
}

void ARoomPlayerController::Server_SetReady_Implementation()
{
	PlayerInfo.bIsReady = true;
	if (ARoomGameMode* RoomGameMode = Cast<ARoomGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		RoomGameMode->RefreshPlayerInfo();
	}
}

void ARoomPlayerController::Server_StartGame_Implementation(const FString& MapName)
{
	if (!CanStartGame()) return;

	if (UGunplayGameInstance::IsLanOnline())
	{
		Server_DestroySessions();
	}

	const FString MapPath = FString::Printf(TEXT("servertravel /Game/Maps/%s"), *MapName);
	UKismetSystemLibrary::ExecuteConsoleCommand(this, MapPath);
	if (ARoomGameMode* RoomGameMode = Cast<ARoomGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		RoomGameMode->StartGame();
		for (ARoomPlayerController* OnlinePlayerController : RoomGameMode->GetRoomPlayerControllers())
		{
			OnlinePlayerController->Client_StartingGame();
		}
	}
}

void ARoomPlayerController::Server_SetPlayerCharacterColor_Implementation(const FVector& Color)
{
	const FUniqueNetIdRepl UniqueNetId = GetPlayerState<APlayerState>()->GetUniqueId();
	UGunplayGameInstance::GetInstance()->SetPlayerCharacterColor(UniqueNetId, Color);
}

void ARoomPlayerController::Server_SetMapItemIndex_Implementation(const int32 NewValue)
{
	if (ARoomGameMode* RoomGameMode = Cast<ARoomGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		RoomGameMode->SetMapItemIndex(NewValue);
	}
}

void ARoomPlayerController::SetMapItemIndex(const int32 NewValue)
{
	MapItemIndex = NewValue;
	OnRep_MapItemIndex();
}

void ARoomPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARoomPlayerController, bIsHost)
	DOREPLIFETIME(ARoomPlayerController, MapItemIndex)
}

void ARoomPlayerController::Server_DestroySessions_Implementation()
{
	if (ARoomGameMode* RoomGameMode = Cast<ARoomGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		for (const ARoomPlayerController* OnlinePlayerController : RoomGameMode->GetRoomPlayerControllers())
		{
			if (UGunplayGameInstance* OnlineGameInstance = Cast<
				UGunplayGameInstance>(UGameplayStatics::GetGameInstance(OnlinePlayerController)))
			{
				OnlineGameInstance->DestroySession();
			}
		}
	}
}

bool ARoomPlayerController::CanStartGame() const
{
	bool bCanStartGame = true;
	if (ARoomGameMode* RoomGameMode = Cast<ARoomGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		for (const FPlayerInfo& ConnectedPlayerInfo : RoomGameMode->GetConnectedPlayerInfos())
		{
			if (!ConnectedPlayerInfo.bIsHost && !ConnectedPlayerInfo.bIsReady)
			{
				bCanStartGame = false;
			}
		}
	}
	return bCanStartGame;
}

void ARoomPlayerController::OnRep_MapItemIndex()
{
	if (RoomWidget)
	{
		RoomWidget->SetMapItemIndex(MapItemIndex);
	}
}
