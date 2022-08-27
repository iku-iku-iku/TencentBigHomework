#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScoreGameMode.generated.h"

UCLASS(minimalapi)
class AScoreGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	AScoreGameMode();

	UFUNCTION(BlueprintPure, Category="Game")
	bool IsGameEnd() const { return bGameEnd; }

	UFUNCTION(BlueprintPure, Category="Game")
	float GetRemainingTime() const { return CountDownTimer; }

protected:
	UPROPERTY(BlueprintReadOnly, Category="Game")
	bool bGameEnd = false;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	float CountDownTimer = 300;

	void SetCountDownTimer(const float NewValue);

	void EndGame() const;

	int32 Client_CountDownTimer;

	void SynchronizeCountDownTimer() const;

	virtual void Tick(float DeltaSeconds) override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;
private:
	int32 PlayerCount;
};
