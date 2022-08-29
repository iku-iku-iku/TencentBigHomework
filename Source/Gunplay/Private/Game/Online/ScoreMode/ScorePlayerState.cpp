// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/ScoreMode/ScorePlayerState.h"

void AScorePlayerState::SetScore(const int32 NewValue)
{
	APlayerState::SetScore(NewValue > 0 ? NewValue : 0);
}

void AScorePlayerState::AddScore(const int32 Delta)
{
	SetScore(GetScore() + Delta);
}
