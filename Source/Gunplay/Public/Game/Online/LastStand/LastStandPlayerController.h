// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GunplayCharacter.h"
#include "Game/Online/OnlinePlayerController.h"
#include "LastStandPlayerController.generated.h"


UCLASS()
class GUNPLAY_API ALastStandPlayerController : public AOnlinePlayerController
{
	GENERATED_BODY()

protected:

	virtual void OnPlayerDeath(const APlayerCharacter* GunplayCharacter) override;

	// 出局
	void KnockedOut() const;

private:
	FTimerHandle RespawnTimerHandle;
};
