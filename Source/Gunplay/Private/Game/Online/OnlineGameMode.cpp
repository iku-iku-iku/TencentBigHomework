#include "Game/Online/OnlineGameMode.h"

#include "Engine/World.h"
#include "Game/GunplayGameInstance.h"
#include "Game/Online/OnlinePlayerController.h"
#include "Kismet/GameplayStatics.h"

void AOnlineGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
                              FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	UE_LOG(LogGameMode, Warning, TEXT("一个玩家想要登录"))
	UE_LOG(LogGameMode, Warning, TEXT("Options: %s"), *Options)
	UE_LOG(LogGameMode, Warning, TEXT("Address: %s"), *Address)
	UE_LOG(LogGameMode, Warning, TEXT("UniqueId: %s"), *UniqueId.ToString())

#ifndef WITH_EDITOR
		if (! UGunplayGameInstance::GetInstance()->GetMatchPlayerUniqueNetIds().Contains(UniqueId))
		{
			ErrorMessage = TEXT("Not Enter From Room");
		}
		else if (bGameEnd)
		{
			ErrorMessage = TEXT("Game End");
		}
#endif
}

void AOnlineGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UE_LOG(LogGameMode, Warning, TEXT("一个玩家加入了游戏"))

	++PlayerCount;
}

void AOnlineGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	UE_LOG(LogGameMode, Warning, TEXT("一个玩家退出了游戏"))

	if (--PlayerCount == 0)
	{
		UE_LOG(LogGameMode, Warning, TEXT("所有玩家退出了游戏"))
		if (IsRunningDedicatedServer())
		{
			UGunplayGameInstance::GetInstance()->ResetDSLevel();
		}
	}
}


void AOnlineGameMode::EndGame() const
{
	if (const UWorld* World = GetWorld())
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			if (AOnlinePlayerController* OnlinePlayerController = Cast<AOnlinePlayerController>(It->Get()))
			{
				OnlinePlayerController->Client_EndGame();
			}
		}
	}
}
