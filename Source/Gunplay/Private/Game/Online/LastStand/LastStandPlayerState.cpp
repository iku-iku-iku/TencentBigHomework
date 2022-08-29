// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/LastStand/LastStandPlayerState.h"

#include "Character/Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Util/GunplayUtils.h"


void ALastStandPlayerState::OnRep_LifeNum()
{
}

void ALastStandPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALastStandPlayerState, LifeNum)
}
