// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GunplayCharacter.h"
#include "Game/Online/OnlinePlayerController.h"
#include "ScorePlayerController.generated.h"


UCLASS()
class GUNPLAY_API AScorePlayerController : public AOnlinePlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(Client, Reliable)
	void Client_SetCountDownTimer(const int32 NewValue);

protected:
	UPROPERTY(BlueprintReadOnly, Category="Controller")
	int32 CountDownTimer;

	virtual void OnPlayerDeath(const APlayerCharacter* GunplayCharacter) override;

private:
	FTimerHandle RespawnTimerHandle;
};
