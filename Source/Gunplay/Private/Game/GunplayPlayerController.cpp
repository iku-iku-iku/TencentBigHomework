// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/GunplayPlayerController.h"

#include "TimerManager.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Game/GunplayGameInstance.h"
#include "Game/Online/OnlinePlayerState.h"
#include "Util/GunplayUtils.h"


AGunplayPlayerController::AGunplayPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

void AGunplayPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AGunplayPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ControlledPlayerCharacter = Cast<APlayerCharacter>(InPawn);
		check(ControlledPlayerCharacter)

		ControlledPlayerCharacter->SetOwner(this);

		ControlledPlayerCharacter->OnDeath().AddLambda([this](const AGunplayCharacter* GunplayCharacter)
			{
				if (const APlayerCharacter* DeadPlayerCharacter = Cast<APlayerCharacter>(GunplayCharacter))
				{
					check(HasAuthority())
					if (! bDead)
					{
						bDead = true;
						OnPlayerDeath(DeadPlayerCharacter);
					}
				}
			}
		);
	}
}

void AGunplayPlayerController::OnPlayerDeath(const APlayerCharacter* GunplayCharacter)
{
}

AOnlinePlayerState* AGunplayPlayerController::GetState() const
{
	return GetPlayerState<AOnlinePlayerState>();
}
