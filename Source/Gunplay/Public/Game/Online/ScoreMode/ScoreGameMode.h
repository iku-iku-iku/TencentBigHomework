#pragma once

#include "CoreMinimal.h"
#include "Game/Online/OnlineGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "ScoreGameMode.generated.h"

UCLASS(minimalapi)
class AScoreGameMode : public AOnlineGameMode
{
	GENERATED_BODY()


public:
	AScoreGameMode();

	UFUNCTION(BlueprintPure, Category="Game")
	float GetRemainingTime() const { return CountDownTimer; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
	float CountDownTimer = 300;

	void SetCountDownTimer(const float NewValue);

	int32 Client_CountDownTimer;

	void SynchronizeCountDownTimer() const;

	virtual void Tick(float DeltaSeconds) override;
};
