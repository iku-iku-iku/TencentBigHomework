// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/CharacterStatusComponent.h"
#include "Character/GunplayCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Game/Online/OnlinePlayerState.h"

UCharacterStatusComponent::UCharacterStatusComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		ACharacter* OwnerCharacter = Cast<ACharacter>(Owner);
		if (OwnerCharacter)
		{
			CharacterOwner = Cast<AGunplayCharacter>(OwnerCharacter);
			PlayerMovementComponent = OwnerCharacter->GetCharacterMovement();
		}
	}

	SetSpeed(Speed);
}

void UCharacterStatusComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterStatusComponent, Attack)
	DOREPLIFETIME(UCharacterStatusComponent, Defense)
	DOREPLIFETIME(UCharacterStatusComponent, Speed)
	DOREPLIFETIME(UCharacterStatusComponent, HP)
	DOREPLIFETIME(UCharacterStatusComponent, MaxHP)
}


void UCharacterStatusComponent::SetHP(const int32 NewValue)
{
	HP = NewValue > 0 ? NewValue : 0;
	if (HP == 0 && CharacterOwner)
	{
		HPZeroEvent.Broadcast();
	}
}

void UCharacterStatusComponent::SetSpeed(const int32 NewValue)
{
	Speed = NewValue > 0 ? NewValue : 0;
	if (PlayerMovementComponent)
	{
		PlayerMovementComponent->MaxWalkSpeed = NewValue;
	}
}
