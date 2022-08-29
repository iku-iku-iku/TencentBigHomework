// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GunplayCharacter.h"
#include "Game/GunplayPlayerController.h"
#include "OnlinePlayerController.generated.h"

/*
 * 多人游戏的Controller父类
 */
UCLASS()
class GUNPLAY_API AOnlinePlayerController : public AGunplayPlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(Client, Reliable)
	void Client_EndGame();

	UFUNCTION()
	virtual void RespawnPlayer();

protected:
	UPROPERTY()
	TArray<class APlayerStart*> PlayerStarts;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	float RespawnStartOffset = 100.f;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	float RespawnDelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	TSubclassOf<class UPlayerInfoListWidget> PlayerInfoListWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	TSubclassOf<class UUserWidget> EndWidgetClass;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category="Controller")
	void ShowPlayerInfoList();
	
	UFUNCTION(BlueprintCallable, Category="Controller")
	void HidePlayerInfoList();

private:
	FTimerHandle RespawnTimerHandle;

	UPROPERTY()
	class UPlayerInfoListWidget* PlayerInfoListWidget;

	bool bIsGameEnd;
};
