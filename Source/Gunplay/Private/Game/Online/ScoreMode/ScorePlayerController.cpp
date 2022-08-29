// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/ScoreMode/ScorePlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Character/GunplayCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Online/OnlinePlayerController.h"

void AScorePlayerController::Client_SetCountDownTimer_Implementation(const int32 NewValue)
{
	CountDownTimer = NewValue;
}

void AScorePlayerController::OnPlayerDeath(const APlayerCharacter* GunplayCharacter)
{
	Super::OnPlayerDeath(GunplayCharacter);

	if (APlayerCharacter* PlayerCharacter = const_cast<APlayerCharacter*>(GunplayCharacter))
	{
		PlayerCharacter->Die();
	}

	PlayerState->SetIsSpectator(true);
	ChangeState(NAME_Spectating);
	
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AScorePlayerController::RespawnPlayer,
	                                RespawnDelayTime, false);
}
