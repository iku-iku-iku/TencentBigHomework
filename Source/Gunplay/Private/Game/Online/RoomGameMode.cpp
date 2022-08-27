// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/RoomGameMode.h"
#include "TimerManager.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Game/GunplayGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game/Online/RoomPlayerController.h"
#include "GameFramework/GameSession.h"

void ARoomGameMode::RefreshPlayerInfo()
{
	ConnectedPlayerInfos.Reset();

	for (ARoomPlayerController* ConnectedPlayerController : ConnectedPlayerControllers)
	{
		ConnectedPlayerInfos.Add(ConnectedPlayerController->GetPlayerInfo());
	}

	for (ARoomPlayerController* PlayerController : ConnectedPlayerControllers)
	{
		PlayerController->Client_UpdatePlayerList(ConnectedPlayerInfos);
	}
}

void ARoomGameMode::StartGame()
{
	bStartGame = true;
}

void ARoomGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
                             FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	UE_LOG(LogGameMode, Warning, TEXT("一个玩家想要进入房间"))
	UE_LOG(LogGameMode, Warning, TEXT("Options: %s"), *Options)
	UE_LOG(LogGameMode, Warning, TEXT("Address: %s"), *Address)
	UE_LOG(LogGameMode, Warning, TEXT("UniqueId: %s"), *UniqueId.ToString())

	UGunplayGameInstance::GetInstance()->GetMatchPlayerUniqueNetIds().Add(UniqueId);
}

void ARoomGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogGameMode, Warning, TEXT("一个新玩家进入了房间"))

	if (ARoomPlayerController* RoomPlayerController = Cast<ARoomPlayerController>(NewPlayer))
	{
		ConnectedPlayerControllers.Add(RoomPlayerController);

		if (++PlayerCount == 1)
		{
			RoomPlayerController->SetIsHost(true);
		}

		// 等待bIsHost同步
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [RoomPlayerController, this, &TimerHandle]
		{
			RoomPlayerController->Client_FillPlayerInfo();
			RoomPlayerController->Client_CreateRoomWidget();

			// 等待PlayerInfo同步
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this] { RefreshPlayerInfo(); }, 0.5f, false);
		}, 0.5f, false);
	}
}

void ARoomGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	UE_LOG(LogGameMode, Warning, TEXT("一个玩家退出了房间"))

	if (--PlayerCount == 0)
	{
		if (! bStartGame)
		{
			UE_LOG(LogGameMode, Warning, TEXT("所有玩家退出了房间"))
			if (IsRunningDedicatedServer())
			{
				UGunplayGameInstance::GetInstance()->ResetDSLevel();
			}
		}
	}
}
