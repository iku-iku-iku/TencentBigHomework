// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RoomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API ARoomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void RefreshPlayerInfo();

	FORCEINLINE TArray<class ARoomPlayerController*>& GetOnlinePlayerControllers()
	{
		return ConnectedPlayerControllers;
	}

	FORCEINLINE TArray<struct FPlayerInfo>& GetConnectedPlayerInfos() { return ConnectedPlayerInfos; }

	void StartGame();
protected:
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	
	virtual void PostLogin(class APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

private:
	UPROPERTY()
	TArray<class ARoomPlayerController*> ConnectedPlayerControllers;

	TArray<struct FPlayerInfo> ConnectedPlayerInfos;

	int32 PlayerCount;

	bool bStartGame;
};
