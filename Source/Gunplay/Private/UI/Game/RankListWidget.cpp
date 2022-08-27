// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/RankListWidget.h"

#include "Components/VerticalBox.h"
#include "Game/Online/OnlineGunplayGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Online/OnlinePlayerState.h"

void URankListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

	if (AOnlineGunplayGameState* OnlineGunplayGameState = Cast<AOnlineGunplayGameState>(
		UGameplayStatics::GetGameState(GetWorld())))
	{
		OnlineGunplayGameState->OnRankReorder().AddLambda([this]
		{
			if (GetVisibility() != ESlateVisibility::Hidden)
			{
				UpdateRankItems();
			}
		});
	}
}

void URankListWidget::UpdateRankItems()
{
	if (RankList)
	{
		RankList->ClearChildren();

		if (const AOnlineGunplayGameState* OnlineGunplayGameState = Cast<AOnlineGunplayGameState>(
			UGameplayStatics::GetGameState(GetWorld())))
		{
			TArray<APlayerState*> PlayerStates = OnlineGunplayGameState->GetPlayerStates();

			for (APlayerState* PlayerState : PlayerStates)
			{
				if (URankListItemWidget* RankListItemWidget = CreateWidget<
					URankListItemWidget>(this, RankListItemClass))
				{
					RankListItemWidget->Inject(Cast<AOnlinePlayerState>(PlayerState));
					RankList->AddChild(RankListItemWidget);
				}
			}
		}
	}
}
