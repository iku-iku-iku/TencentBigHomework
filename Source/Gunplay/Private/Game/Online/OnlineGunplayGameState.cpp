// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/OnlineGunplayGameState.h"

#include "Algo/IsSorted.h"
#include "GameFramework/PlayerState.h"
#include "Game/Online/OnlinePlayerState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"

namespace
{
	auto StateRefComparator = [](const APlayerState& Lhs, const APlayerState& Rhs)
	{
		return Lhs.GetScore() > Rhs.GetScore();
	};

	auto StatePtrComparator = [](const APlayerState* Lhs, const APlayerState* Rhs)
	{
		return Lhs->GetScore() > Rhs->GetScore();
	};
}

AOnlineGunplayGameState::AOnlineGunplayGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOnlineGunplayGameState::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]{ReorderPlayerStates();}, 0.2f, false);
}

void AOnlineGunplayGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (! Algo::IsSorted(PlayerArray, StatePtrComparator))
	{
		ReorderPlayerStates();
	}
}

void AOnlineGunplayGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	ReorderPlayerStates();

	UE_LOG(LogNet, Warning, TEXT("Add Player"))
}

void AOnlineGunplayGameState::ReorderPlayerStates()
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

int32 AOnlineGunplayGameState::GetPlayerRank(const APlayerState* PlayerState) const
{
	return PlayerArray.IndexOfByKey(PlayerState) + 1;
}

APlayerState* AOnlineGunplayGameState::GetAheadPlayer(const APlayerState* PlayerState) const
{
	const int Index = PlayerArray.IndexOfByKey(PlayerState);
	if (Index > 0)
	{
		return PlayerArray[Index - 1];
	}
	return nullptr;
}

APlayerState* AOnlineGunplayGameState::GetBehindPlayer(const APlayerState* PlayerState) const
{
	const int Index = PlayerArray.IndexOfByKey(PlayerState);
	if (Index < PlayerArray.Num() - 1)
	{
		return PlayerArray[Index + 1];
	}
	return nullptr;
}
