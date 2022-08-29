// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/LastStand/LastStandGameState.h"

#include "GameFramework/PlayerState.h"
#include "Engine/World.h"
#include "Game/Online/LastStand/LastStandPlayerState.h"

ALastStandGameState::ALastStandGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StateRefComparator = [](const APlayerState& Lhs, const APlayerState& Rhs)
	{
		const ALastStandPlayerState* LhsState = Cast<ALastStandPlayerState>(&Lhs);
		const ALastStandPlayerState* RhsState = Cast<ALastStandPlayerState>(&Rhs);
		return LhsState && RhsState && LhsState->GetLifeNum() > RhsState->GetLifeNum();
	};

	StatePtrComparator = [](const APlayerState* Lhs, const APlayerState* Rhs)
	{
		const ALastStandPlayerState* LhsState = Cast<ALastStandPlayerState>(Lhs);
		const ALastStandPlayerState* RhsState = Cast<ALastStandPlayerState>(Rhs);
		return LhsState && RhsState && LhsState->GetLifeNum() > RhsState->GetLifeNum();
	};
}
