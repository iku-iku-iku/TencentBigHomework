// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Solitary/ExtremeSurvivalPlayerController.h"

#include "Character/Player/PlayerCharacter.h"
#include "Blueprint/UserWidget.h"

void AExtremeSurvivalPlayerController::OnPlayerDeath(const APlayerCharacter* GunplayCharacter)
{
	Super::OnPlayerDeath(GunplayCharacter);

	
	if (APlayerCharacter* PlayerCharacter = const_cast<APlayerCharacter*>(GunplayCharacter))
	{
		PlayerCharacter->Die();
	}

	if (UUserWidget* UserWidget = CreateWidget(this, DeadUI))
	{
		UserWidget->AddToViewport();
	}
}
