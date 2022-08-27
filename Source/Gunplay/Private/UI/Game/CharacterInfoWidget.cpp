// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/CharacterInfoWidget.h"

#include "Component/CharacterStatusComponent.h"
#include "Character/GunplayCharacter.h"
#include "Component/HoldComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "Holding/Grenade.h"
#include "Holding/Gun.h"
#include "Holding/MainCharacterGun.h"


void UCharacterInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HPBar->PercentDelegate.BindDynamic(this, &UCharacterInfoWidget::GetHPRatio);
	HPText->TextDelegate.BindDynamic(this, &UCharacterInfoWidget::GetHPRatioText);
	SpeedText->TextDelegate.BindDynamic(this, &UCharacterInfoWidget::GetSpeedText);
	DefenseText->TextDelegate.BindDynamic(this, &UCharacterInfoWidget::GetDefenseText);
	AttackText->TextDelegate.BindDynamic(this, &UCharacterInfoWidget::GetAttackText);
	HoldingNameText->TextDelegate.BindDynamic(this, &UCharacterInfoWidget::GetHoldingText);
	HoldingCapacityText->TextDelegate.BindDynamic(this, &UCharacterInfoWidget::GetHoldingCapacityText);
}

float UCharacterInfoWidget::GetHPRatio()
{
	if (const APlayerState* PlayerState = GetOwningPlayerState())
	{
		if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(PlayerState->GetPawn()))
		{
			return GunplayCharacter->GetStatus()->GetHPRatio();
		}
	}
	return 0;
}

FText UCharacterInfoWidget::GetHPRatioText()
{
	if (const APlayerState* PlayerState = GetOwningPlayerState())
	{
		if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(PlayerState->GetPawn()))
		{
			const UCharacterStatusComponent* Status = GunplayCharacter->GetStatus();
			return FText::FromString(FString::Printf(TEXT("%d / %d"), Status->GetHP(), Status->GetMaxHP()));
		}
	}
	return {};
}

FText UCharacterInfoWidget::GetSpeedText()
{
	if (const APlayerState* PlayerState = GetOwningPlayerState())
	{
		if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(PlayerState->GetPawn()))
		{
			const UCharacterStatusComponent* Status = GunplayCharacter->GetStatus();
			return FText::FromString(FString::FromInt(Status->GetSpeed()));
		}
	}
	return {};
}

FText UCharacterInfoWidget::GetAttackText()
{
	if (const APlayerState* PlayerState = GetOwningPlayerState())
	{
		if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(PlayerState->GetPawn()))
		{
			const UCharacterStatusComponent* Status = GunplayCharacter->GetStatus();
			return FText::FromString(FString::FromInt(Status->GetAttack()));
		}
	}
	return {};
}

FText UCharacterInfoWidget::GetDefenseText()
{
	if (const APlayerState* PlayerState = GetOwningPlayerState())
	{
		if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(PlayerState->GetPawn()))
		{
			const UCharacterStatusComponent* Status = GunplayCharacter->GetStatus();
			return FText::FromString(FString::FromInt(Status->GetDefense()));
		}
	}
	return {};
}

FText UCharacterInfoWidget::GetHoldingText()
{
	if (const APlayerState* PlayerState = GetOwningPlayerState())
	{
		if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(PlayerState->GetPawn()))
		{
			if (const UHoldComponent* HoldingComponent = GunplayCharacter->GetHoldingComponent())
			{
				if (const AActor* Holding = HoldingComponent->GetCurrentHolding())
				{
					const UClass* HoldingClass = Holding->GetClass();
					if (HoldingClass->IsChildOf(AGrenade::StaticClass()))
					{
						return FText::FromString(TEXT("手榴弹"));
					}
					if (HoldingClass->IsChildOf(AMainCharacterGun::StaticClass()))
					{
						return FText::FromString(TEXT("炫彩枪"));
					}
				}
			}
		}
	}
	return {};
}

FText UCharacterInfoWidget::GetHoldingCapacityText()
{
	if (const APlayerState* PlayerState = GetOwningPlayerState())
	{
		if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(PlayerState->GetPawn()))
		{
			if (const UHoldComponent* HoldingComponent = GunplayCharacter->GetHoldingComponent())
			{
				if (const AActor* Holding = HoldingComponent->GetCurrentHolding())
				{
					if (const AGun* Gun = Cast<AGun>(Holding))
					{
						return FText::FromString(
							FString::Printf(TEXT("%d"), Gun->GetBulletNum()));
					}
					if (Cast<AGrenade>(Holding))
					{
						return FText::FromString(FString::Printf(
							TEXT("x%d"),
							GunplayCharacter->GetHoldingComponent()->GetHoldingNum(AGrenade::StaticClass())));
					}
				}
			}
		}
	}
	return {};
}
