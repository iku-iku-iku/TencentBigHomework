// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GunplayCharacter.h"
#include "Game/GunplayPlayerController.h"
#include "OnlinePlayerController.generated.h"


UCLASS()
class GUNPLAY_API AOnlinePlayerController : public AGunplayPlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(Client, Reliable)
	void Client_EndGame();
	
	UFUNCTION(Client, Reliable)
	void Client_SetCountDownTimer(const int32 NewValue);

protected:
	UPROPERTY(BlueprintReadOnly, Category="Controller")
	int32 CountDownTimer;
	
	UPROPERTY()
	TArray<class APlayerStart*> PlayerStarts;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	float RespawnStartOffset = 100.f;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	float RespawnDelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	TSubclassOf<class URankListWidget> RankListWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	TSubclassOf<class UUserWidget> EndWidgetClass;

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void OnPlayerDeath(const APlayerCharacter* GunplayCharacter) override;

	UFUNCTION()
	void RespawnPlayer();

	UFUNCTION(BlueprintCallable, Category="Controller")
	void ShowRankList();
	
	UFUNCTION(BlueprintCallable, Category="Controller")
	void HideRankList();

private:
	FTimerHandle RespawnTimerHandle;

	UPROPERTY()
	class URankListWidget* RankListWidget;

	bool bIsGameEnd;
};
