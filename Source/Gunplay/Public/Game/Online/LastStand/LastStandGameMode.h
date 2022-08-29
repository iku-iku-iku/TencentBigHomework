#pragma once

#include "CoreMinimal.h"
#include "Game/Online/OnlineGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "LastStandGameMode.generated.h"

UCLASS(minimalapi)
class ALastStandGameMode : public AOnlineGameMode
{
	GENERATED_BODY()

public:
	ALastStandGameMode();

	void KnockOutPlayer();

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly, Category="LastStand")
	int32 PlayerInitialLifeNum = 10;

private:
	// 活着的玩家数
	int32 AliveNum;
};
