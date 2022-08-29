// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RoomGameMode.generated.h"

/**
 * 房间模式：最先进入的玩家为房主，房主可以选择游戏模式
 * 当所有玩家准备好后，房主可以开始游戏
 */
UCLASS()
class GUNPLAY_API ARoomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void RefreshPlayerInfo();

	FORCEINLINE TArray<class ARoomPlayerController*>& GetRoomPlayerControllers()
	{
		return ConnectedPlayerControllers;
	}

	FORCEINLINE TArray<struct FPlayerInfo>& GetConnectedPlayerInfos() { return ConnectedPlayerInfos; }

	void StartGame();

	void SetMapItemIndex(const int32 NewValue);
	
	FORCEINLINE int32 GetMapItemIndex() const { return MapItemIndex; }

protected:
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
	                      FString& ErrorMessage) override;

	virtual void PostLogin(class APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

private:
	UPROPERTY()
	TArray<class ARoomPlayerController*> ConnectedPlayerControllers;

	TArray<struct FPlayerInfo> ConnectedPlayerInfos;

	int32 PlayerCount;

	bool bStartGame;

	int32 MapItemIndex = 0;
};
