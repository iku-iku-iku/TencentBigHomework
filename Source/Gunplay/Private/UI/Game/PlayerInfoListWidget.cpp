// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/PlayerInfoListWidget.h"

#include "Components/VerticalBox.h"
#include "Game/Online/OnlineGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Online/OnlinePlayerState.h"
#include "UI/Item/PlayerInfoListItemWidget.h"

void UPlayerInfoListWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

	if (AOnlineGameState* OnlineGunplayGameState = Cast<AOnlineGameState>(
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

void UPlayerInfoListWidget::UpdateRankItems()
{
	if (PlayerInfoList)
	{
		PlayerInfoList->ClearChildren();

		if (const AOnlineGameState* OnlineGunplayGameState = Cast<AOnlineGameState>(
			UGameplayStatics::GetGameState(GetWorld())))
		{
			TArray<APlayerState*> PlayerStates = OnlineGunplayGameState->GetPlayerStates();

			for (APlayerState* PlayerState : PlayerStates)
			{
				if (UPlayerInfoListItemWidget* RankListItemWidget = CreateWidget<
					UPlayerInfoListItemWidget>(this, ListItemClass))
				{
					RankListItemWidget->Inject(Cast<AOnlinePlayerState>(PlayerState));
					PlayerInfoList->AddChild(RankListItemWidget);
				}
			}
		}
	}
}
