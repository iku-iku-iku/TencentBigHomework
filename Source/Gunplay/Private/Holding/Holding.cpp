// Copyright iku-iku-iku,. All Rights Reserved.


#include "Holding/Holding.h"

#include "Character/GunplayCharacter.h"
#include "GameFramework/PlayerController.h"

AHolding::AHolding()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AHolding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHolding, Holder);
}

void AHolding::BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter)
{
	if (HasAuthority())
	{
		Holder = GunplayCharacter;
	}
}
