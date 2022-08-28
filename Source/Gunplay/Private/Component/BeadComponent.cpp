// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/BeadComponent.h"

#include "Character/GunplayCharacter.h"
#include "Component/AnimationComponent.h"
#include "Game/GunplayGameInstance.h"
#include "Game/GunplayPlayerController.h"
#include "Holding/Holding.h"
#include "UI/Game/BeadWidget.h"

UBeadComponent::UBeadComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UBeadComponent::GetBaseRadius() const
{
	bool bIsAiming = false;
	if (const AHolding* Holding = Cast<AHolding>(GetOwner()))
	{
		if (const AGunplayCharacter* GunplayCharacter = Holding->GetHolder())
		{
			if (GunplayCharacter->GetAnimationComponent()->IsAiming())
			{
				bIsAiming = true;
			}
		}
	}
	return bIsAiming ? AimBaseBeadRadius : BaseBeadRadius;
}

void UBeadComponent::GetBeadRandPoint(FVector& WorldLocation, FVector& WorldDirection)
{
	if (UBeadWidget* BeadWidget = UGunplayGameInstance::GetSingleton<UBeadWidget>())
	{
		BeadWidget->GetRandomPoint(WorldLocation, WorldDirection);
	}
}
