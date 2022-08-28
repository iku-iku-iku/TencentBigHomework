// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/AnimationComponent.h"

#include "Character/GunplayCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/HoldComponent.h"
#include "Animation/AnimInstance.h"

#include "Net/UnrealNetwork.h"

UAnimationComponent::UAnimationComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = true;
}

void UAnimationComponent::BeginPlay()
{
	Super::BeginPlay();
	if (AGunplayCharacter* OwnerCharacter = Cast<AGunplayCharacter>(GetOwner()))
	{
		OwnerCharacter->GetHoldingComponent()->OnSwitchHolding().AddLambda([this, OwnerCharacter]
		{
			if (const USkeletalMeshComponent* SkeletalMeshComponent = OwnerCharacter->GetMesh())
			{
				if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
				{
					AnimInstance->StopAllMontages(.1f);
				}
			}
			SetIsShooting(false);
			SetAiming(false);
		});
	}
}

void UAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAnimationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAnimationComponent, bInAir)
	DOREPLIFETIME(UAnimationComponent, bWantToJump)
	DOREPLIFETIME(UAnimationComponent, bShooting)
	DOREPLIFETIME(UAnimationComponent, bAiming)
	DOREPLIFETIME(UAnimationComponent, HorizontalOrientation)
	DOREPLIFETIME(UAnimationComponent, VerticalOrientation)
}

void UAnimationComponent::SetAiming(bool NewValue)
{
	if (NewValue != bAiming)
	{
		bAiming = NewValue;
		Server_SetAiming(NewValue);
	}
}

void UAnimationComponent::Server_SetAiming_Implementation(const bool NewValue)
{
	bAiming = NewValue;
}

void UAnimationComponent::Server_SetIsShooting_Implementation(const bool NewValue)
{
	bShooting = NewValue;
}

void UAnimationComponent::Server_SetInAir_Implementation(const bool NewValue)
{
	bInAir = NewValue;
}

void UAnimationComponent::SetIsShooting(const bool NewValue)
{
	if (NewValue != bShooting)
	{
		bShooting = NewValue;
		Server_SetIsShooting(NewValue);
	}
}

void UAnimationComponent::Server_SetVerticalOrientation_Implementation(const float NewValue)
{
	VerticalOrientation = NewValue;
}

void UAnimationComponent::Server_SetHorizontalOrientation_Implementation(const float NewValue)
{
	HorizontalOrientation = NewValue;
}

void UAnimationComponent::SetVerticalOrientation(const float NewValue)
{
	if (NewValue != VerticalOrientation)
	{
		VerticalOrientation = NewValue;
		Server_SetVerticalOrientation(NewValue);
	}
}

void UAnimationComponent::Server_SetWantToJump_Implementation(const bool NewValue)
{
	bWantToJump = NewValue;
}

void UAnimationComponent::SetHorizontalOrientation(const float NewValue)
{
	if (NewValue != HorizontalOrientation)
	{
		HorizontalOrientation = NewValue;
		Server_SetHorizontalOrientation(NewValue);
	}
}

void UAnimationComponent::SetWantToJump(const bool NewValue)
{
	if (NewValue != bWantToJump)
	{
		bWantToJump = NewValue;
		Server_SetWantToJump(NewValue);
	}
}

void UAnimationComponent::SetInAir(const bool NewValue)
{
	if (NewValue != bInAir)
	{
		bInAir = NewValue;
		Server_SetInAir(NewValue);
	}
}
