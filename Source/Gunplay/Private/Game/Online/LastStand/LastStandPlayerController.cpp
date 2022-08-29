// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/LastStand/LastStandPlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Character/GunplayCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Game/Online/LastStand/LastStandGameMode.h"
#include "Game/Online/LastStand/LastStandPlayerState.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void ALastStandPlayerController::OnPlayerDeath(const APlayerCharacter* GunplayCharacter)
{
	Super::OnPlayerDeath(GunplayCharacter);

	check(HasAuthority())

	if (APlayerCharacter* PlayerCharacter = const_cast<APlayerCharacter*>(GunplayCharacter))
	{
		PlayerCharacter->Die();
	}

	PlayerState->SetIsSpectator(true);
	ChangeState(NAME_Spectating);

	if (ALastStandPlayerState* OnlinePlayerState = GetPlayerState<ALastStandPlayerState>())
	{
		OnlinePlayerState->SetLifeNum(OnlinePlayerState->GetLifeNum() - 1);

		if (OnlinePlayerState->GetLifeNum() >= 1)
		{
			GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ALastStandPlayerController::RespawnPlayer,
			                                RespawnDelayTime, false);
		}
		else
		{
			KnockedOut();
		}
	}
}

void ALastStandPlayerController::KnockedOut() const
{
	check(HasAuthority())
	if (ALastStandGameMode* LastStandGameMode = Cast<ALastStandGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		LastStandGameMode->KnockOutPlayer();
	}
}
