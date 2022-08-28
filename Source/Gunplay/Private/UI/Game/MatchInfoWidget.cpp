// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/MatchInfoWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Character/GunplayCharacter.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Game/GunplayGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "Game/Online/OnlineGunplayGameState.h"
#include "UI/Item/RankListItemWidget.h"


void UMatchInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AOnlineGunplayGameState* OnlineGunplayGameState = Cast<AOnlineGunplayGameState>(
		UGameplayStatics::GetGameState(GetWorld())))
	{
		OnlineGunplayGameState->OnRankReorder().AddLambda([this]
		{
			UpdateRankItems();
		});
	}
}

void UMatchInfoWidget::UpdateRankItems()
{
	if (RankPreview)
	{
		RankPreview->ClearChildren();

		if (const AOnlineGunplayGameState* OnlineGunplayGameState = Cast<AOnlineGunplayGameState>(
			UGameplayStatics::GetGameState(this)))
		{
			TArray<APlayerState*> PlayerStates = OnlineGunplayGameState->GetPlayerStates();

			int32 PlayerStateIndex = 0;

			for (; PlayerStateIndex < PlayerStates.Num(); PlayerStateIndex++)
			{
				if (PlayerStates[PlayerStateIndex]->GetPlayerName().Equals(UGunplayGameInstance::GetInstance()->GetPlayerName().ToString()))
				{
					break;
				}
			}

			if (PlayerStateIndex == PlayerStates.Num() - 1)
			{
				PlayerStateIndex -= 2;
			}
			else if (PlayerStateIndex != 0)
			{
				PlayerStateIndex -= 1;
			}

			for (int Cnt = 0; Cnt < RankPreviewCount; Cnt++, PlayerStateIndex++)
			{
				if (PlayerStates.IsValidIndex(PlayerStateIndex))
				{
					if (URankListItemWidget* RankListItemWidget = CreateWidget<
						URankListItemWidget>(this, RankListItemClass))
					{
						RankListItemWidget->Inject(Cast<AOnlinePlayerState>(PlayerStates[PlayerStateIndex]));
						RankPreview->AddChild(RankListItemWidget);
					}
				};
			}
		}
	}
}
