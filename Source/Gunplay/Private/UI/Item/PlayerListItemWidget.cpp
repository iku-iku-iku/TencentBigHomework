// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Item/PlayerListItemWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Game/Online/PlayerInfo.h"

void UPlayerListItemWidget::InjectPlayerInfo(const FPlayerInfo& PlayerInfo) const
{
	if (PlayerNameText)
	{
		PlayerNameText->SetText(PlayerInfo.PlayerName);
	}
	if (ReadyStatus)
	{
		if (PlayerInfo.bIsHost)
		{
			ReadyStatus->SetBrushColor(HostColor);
		}
		else
		{
			if (PlayerInfo.bIsReady)
			{
				ReadyStatus->SetBrushColor(ReadyColor);
			}
			else
			{
				ReadyStatus->SetBrushColor(NotReadyColor);
			}
		}
	}
}
