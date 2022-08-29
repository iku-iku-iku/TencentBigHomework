#include "Game/Online/LastStand/LastStandGameMode.h"

#include "Engine/World.h"
#include "Game/GunplayGameInstance.h"
#include "Game/Online/LastStand/LastStandPlayerState.h"
#include "Kismet/GameplayStatics.h"

ALastStandGameMode::ALastStandGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALastStandGameMode::KnockOutPlayer()
{
	AliveNum--;
}

void ALastStandGameMode::BeginPlay()
{
	Super::BeginPlay();

	AliveNum = UGunplayGameInstance::GetInstance()->ConsumePlayerNum();
}

void ALastStandGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bGameEnd) { return; }

	if (AliveNum == 1)
	{
		bGameEnd = true;
		EndGame();
	}
}

void ALastStandGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if (ALastStandPlayerState* LastStandPlayerState = NewPlayer->GetPlayerState<ALastStandPlayerState>())
	{
		LastStandPlayerState->SetLifeNum(PlayerInitialLifeNum);
	}
}
