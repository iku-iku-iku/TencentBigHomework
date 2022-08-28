// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/GunplayPlayerController.h"
#include "ExtremeSurvivalPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API AExtremeSurvivalPlayerController : public AGunplayPlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Player")
	TSubclassOf<class UUserWidget> DeadUI;

	virtual void OnPlayerDeath(const APlayerCharacter* GunplayCharacter) override;
};
