// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Online/RoomWidget.h"

#include "Animation/SkeletalMeshActor.h"
#include "Components/Button.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextBlock.h"
#include "Game/Online/PlayerInfo.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/DataTable.h"
#include "Game/GunplayGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Online/RoomPlayerController.h"
#include "UI/Item/PlayerListItemWidget.h"
#include "Game/Online/MapItemStruct.h"
#include "Util/GunplayUtils.h"


void URoomWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (MapTable)
	{
		MapTableRowNames = MapTable->GetRowNames();
	}

	StartGameBtn->OnClicked.AddDynamic(this, &URoomWidget::StartGame);
	PrepareBtn->OnClicked.AddDynamic(this, &URoomWidget::Prepare);
	ResetColorBtn->OnClicked.AddDynamic(this, &URoomWidget::ResetCharacterColor);

	ResetCharacterColor();
}

void URoomWidget::UpdatePlayerList(const TArray<FPlayerInfo>& PlayerInfos)
{
	if (PlayerList)
	{
		PlayerList->ClearChildren();
		for (const FPlayerInfo& Info : PlayerInfos)
		{
			if (UPlayerListItemWidget* PlayerListItemWidget = CreateWidget<UPlayerListItemWidget>(
				this, PlayerListItemWidgetClass))
			{
				PlayerListItemWidget->InjectPlayerInfo(Info);
				PlayerList->AddChild(PlayerListItemWidget);
			}
		}
	}
}

void URoomWidget::Prepare()
{
	if (ARoomPlayerController* OnlinePlayerController = Cast<ARoomPlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		OnlinePlayerController->Server_SetReady();
	}
}

void URoomWidget::StartGame()
{
	if (ARoomPlayerController* RoomPlayerController = Cast<ARoomPlayerController>(GetOwningPlayer()))
	{
		const FMapItemStruct* MapItemStruct = MapTable->FindRow<FMapItemStruct>(MapTableRowNames[MapItemIndex], "");
		RoomPlayerController->Server_StartGame(*MapItemStruct->Map);
	}
}

void URoomWidget::ResetCharacterColor()
{
	const FVector RandColor = GunplayUtils::FRandVector();

	if (ARoomPlayerController* RoomPlayerController = Cast<ARoomPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		RoomPlayerController->Server_SetPlayerCharacterColor(RandColor);
	}
	
	if (const ASkeletalMeshActor* SkeletalMeshActor = GunplayUtils::GetActorOfClass<ASkeletalMeshActor>(this))
	{
		if (USkeletalMeshComponent* SkeletalMeshComponent = SkeletalMeshActor->GetSkeletalMeshComponent())
		{
			SkeletalMeshComponent->SetVectorParameterValueOnMaterials(TEXT("BodyColor"), RandColor);
		}
	}
}

void URoomWidget::SwitchMapLeft()
{
	if (MapItemIndex > 0)
	{
		MapItemIndex--;
		SetMapItem(MapItemIndex);
	}
}

void URoomWidget::SwitchMapRight()
{
	if (MapItemIndex < MapTableRowNames.Num() - 1)
	{
		MapItemIndex++;
		SetMapItem(MapItemIndex);
	}
}


void URoomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MapItemIndex = 0;
	SetMapItem(0);

	SetUIVisibility();
}

void URoomWidget::SetMapItem(int32 Index)
{
	if (MapTable && Index >= 0 && Index < MapTableRowNames.Num())
	{
		const FMapItemStruct* Item = MapTable->FindRow<FMapItemStruct>(MapTableRowNames[Index], "");
		if (MapNameText)
		{
			MapNameText->SetText(Item->MapName);
		}
	}
}

void URoomWidget::SetUIVisibility() const
{
	if (const ARoomPlayerController* RoomPlayerController = Cast<ARoomPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0)))
	{
		const bool bIsHost = RoomPlayerController->IsHost();

		LeftSwitchMapBtn->SetVisibility(bIsHost ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		RightSwitchMapBtn->SetVisibility(bIsHost ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

		StartOrPrepare->SetActiveWidgetIndex(bIsHost ? 0 : 1);
	}
}
