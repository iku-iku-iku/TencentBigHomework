#include "Game/Online/ScoreMode/ScoreGameMode.h"

#include "Engine/World.h"
#include "Game/GunplayGameInstance.h"
#include "Game/Online/ScoreMode/ScorePlayerController.h"
#include "Kismet/GameplayStatics.h"

AScoreGameMode::AScoreGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScoreGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bGameEnd) { return; }

	SetCountDownTimer(CountDownTimer - DeltaSeconds);

	if (CountDownTimer < 0)
	{
		CountDownTimer = 0;
		bGameEnd = true;
		EndGame();
	}
}

void AScoreGameMode::SetCountDownTimer(const float NewValue)
{
	CountDownTimer = NewValue;

	if (Client_CountDownTimer != static_cast<int32>(NewValue))
	{
		SynchronizeCountDownTimer();
		Client_CountDownTimer = NewValue;
	}
}

void AScoreGameMode::SynchronizeCountDownTimer() const
{
	if (const UWorld* World = GetWorld())
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			if (AScorePlayerController* ScorePlayerController = Cast<AScorePlayerController>(It->Get()))
			{
				ScorePlayerController->Client_SetCountDownTimer(Client_CountDownTimer);
			}
		}
	}
}
