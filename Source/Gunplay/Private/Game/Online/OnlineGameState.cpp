// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/OnlineGameState.h"

#include "Algo/IsSorted.h"
#include "GameFramework/PlayerState.h"
#include "Game/Online/OnlinePlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"


AOnlineGameState::AOnlineGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOnlineGameState::BeginPlay()
{
	TFunction<bool(int, class APlayerState*)> x;
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this] { ReorderPlayerStates(); }, 0.2f, false);
}

void AOnlineGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (! Algo::IsSorted(PlayerArray, StatePtrComparator))
	{
		ReorderPlayerStates();
	}
}

void AOnlineGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	ReorderPlayerStates();

	UE_LOG(LogNet, Warning, TEXT("Add Player"))
}

void AOnlineGameState::ReorderPlayerStates()
{
	PlayerArray.StableSort(StateRefComparator);

	for (int i = 0; i < PlayerArray.Num(); i++)
	{
		if (AOnlinePlayerState* MultiPlayerState = Cast<AOnlinePlayerState>(PlayerArray[i]))
		{
			MultiPlayerState->SetRank(i + 1);
		}
	}

	RankReorderEvent.Broadcast();
}

int32 AOnlineGameState::GetPlayerRank(const APlayerState* PlayerState) const
{
	return PlayerArray.IndexOfByKey(PlayerState) + 1;
}

APlayerState* AOnlineGameState::GetAheadPlayer(const APlayerState* PlayerState) const
{
	const int Index = PlayerArray.IndexOfByKey(PlayerState);
	if (Index > 0)
	{
		return PlayerArray[Index - 1];
	}
	return nullptr;
}

APlayerState* AOnlineGameState::GetBehindPlayer(const APlayerState* PlayerState) const
{
	const int Index = PlayerArray.IndexOfByKey(PlayerState);
	if (Index < PlayerArray.Num() - 1)
	{
		return PlayerArray[Index + 1];
	}
	return nullptr;
}
