// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Item/LastStandListItemWidget.h"

#include "Components/TextBlock.h"
#include "Game/GunplayGameInstance.h"
#include "Game/Online/LastStand/LastStandPlayerState.h"

void ULastStandListItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LifeNum) { LifeNum->TextDelegate.BindDynamic(this, &ULastStandListItemWidget::GetLifeNum); }
	if (Name)
	{
		Name->TextDelegate.BindDynamic(this, &ULastStandListItemWidget::GetPlayerName);
		Name->ColorAndOpacityDelegate.BindDynamic(this, &ULastStandListItemWidget::GetNameColor);
	}
	if (Rank) { Rank->TextDelegate.BindDynamic(this, &ULastStandListItemWidget::GetRank); }
}

FText ULastStandListItemWidget::GetLifeNum()
{
	if (const ALastStandPlayerState* LastStandPlayerState = Cast<ALastStandPlayerState>(PlayerState))
	{
		return FText::FromString(FString::FromInt(LastStandPlayerState->GetLifeNum()));
	}
	return {};
}

FText ULastStandListItemWidget::GetPlayerName()
{
	if (PlayerState)
	{
		return FText::FromString(PlayerState->GetPlayerName());
	}
	return {};
}

FText ULastStandListItemWidget::GetRank()
{
	if (PlayerState)
	{
		return FText::FromString(FString::FromInt(PlayerState->GetRank()));
	}
	return {};
}

FSlateColor ULastStandListItemWidget::GetNameColor()
{
	if (PlayerState)
	{
		const bool bIsLocalPlayer = PlayerState->GetPlayerName().Equals(
			UGunplayGameInstance::GetInstance()->GetPlayerName().ToString());
		if (bIsLocalPlayer)
		{
			return FSlateColor(FLinearColor::Red);
		}
	}
	return FSlateColor(FLinearColor::White);
}
