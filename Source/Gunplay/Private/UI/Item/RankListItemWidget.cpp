// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Item/RankListItemWidget.h"

#include "Components/TextBlock.h"
#include "Game/GunplayGameInstance.h"

void URankListItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Score) { Score->TextDelegate.BindDynamic(this, &URankListItemWidget::GetScore); }
	if (Name)
	{
		Name->TextDelegate.BindDynamic(this, &URankListItemWidget::GetPlayerName);
		Name->ColorAndOpacityDelegate.BindDynamic(this, &URankListItemWidget::GetNameColor);
	}
	if (Rank) { Rank->TextDelegate.BindDynamic(this, &URankListItemWidget::GetRank); }
}

FText URankListItemWidget::GetScore()
{
	if (PlayerState)
	{
		return FText::FromString(FString::FromInt(PlayerState->GetPlayerScore()));
	}
	return {};
}

FText URankListItemWidget::GetPlayerName()
{
	if (PlayerState)
	{
		return FText::FromString(PlayerState->GetPlayerName());
	}
	return {};
}

FText URankListItemWidget::GetRank()
{
	if (PlayerState)
	{
		return FText::FromString(FString::FromInt(PlayerState->GetRank()));
	}
	return {};
}

FSlateColor URankListItemWidget::GetNameColor()
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
