// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/ScoreMode//ScoreGameState.h"

#include "GameFramework/PlayerState.h"
#include "Engine/World.h"

AScoreGameState::AScoreGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StateRefComparator = [](const APlayerState& Lhs, const APlayerState& Rhs)
	{
		return Lhs.GetScore() > Rhs.GetScore();
	};
	
	StatePtrComparator = [](const APlayerState* Lhs, const APlayerState* Rhs)
	{
		return Lhs->GetScore() > Rhs->GetScore();
	};
	
}
