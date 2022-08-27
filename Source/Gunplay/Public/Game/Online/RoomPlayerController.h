// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.h"
#include "GameFramework/PlayerController.h"
#include "RoomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API ARoomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void Client_UpdatePlayerList(const TArray<struct FPlayerInfo>& PlayerInfos);

	UFUNCTION(Client, Reliable)
	void Client_StartingGame();

	UFUNCTION(Client, Reliable)
	void Client_CreateRoomWidget();

	UFUNCTION(Client, Reliable)
	void Client_FillPlayerInfo();

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerInfo(const FPlayerInfo& NewValue);

	UFUNCTION(Server, Reliable)
	void Server_SetReady();

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerCharacterColor(const FVector& Color);

	UFUNCTION(Server, Reliable)
	void Server_StartGame(const FString& MapName);
	
public:
	FORCEINLINE FPlayerInfo GetPlayerInfo() { return PlayerInfo; }

	FORCEINLINE bool IsHost() const { return bIsHost; }

	FORCEINLINE void SetIsHost(const bool NewValue) { bIsHost = NewValue; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FPlayerInfo PlayerInfo;

	UPROPERTY()
	class URoomWidget* RoomWidget;

	UPROPERTY(EditDefaultsOnly, Category="Online")
	TSubclassOf<class ULoadingWidget> LoadingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Online")
	TSubclassOf<class URoomWidget> RoomWidgetClass;

	UPROPERTY(Replicated)
	bool bIsHost;

private:
	UFUNCTION(Server, Reliable)
	void Server_DestroySessions();

	bool CanStartGame() const;
};
