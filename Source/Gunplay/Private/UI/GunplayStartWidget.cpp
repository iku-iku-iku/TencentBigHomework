// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/GunplayStartWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Game/GunplayGameInstance.h"
#include "UI/Util/DialogWidget.h"

void UGunplayStartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SolitaryBtn->OnClicked.AddDynamic(this, &UGunplayStartWidget::OnSolitaryClicked);
	LANBtn->OnClicked.AddDynamic(this, &UGunplayStartWidget::OnLANClicked);
	DSBtn->OnClicked.AddDynamic(this, &UGunplayStartWidget::OnDSClicked);
}

void UGunplayStartWidget::OnSolitaryClicked()
{
	if (UGunplayGameInstance* GameInstance = Cast<UGunplayGameInstance>(GetGameInstance()))
	{
		GameInstance->SetGunplayMode(EGunplayMode::Solitary);
	}

	UGameplayStatics::OpenLevel(this, SolitaryLevel);
}

void UGunplayStartWidget::StartLANMode(UGunplayGameInstance* GunplayGameInstance) const
{
	GunplayGameInstance->SetGunplayMode(EGunplayMode::LanOnline);
	GunplayGameInstance->ShowLoading(TEXT("正在进入大厅"));
	UGameplayStatics::OpenLevel(this, LANLevel);
}

void UGunplayStartWidget::OnLANClicked()
{
	if (UGunplayGameInstance* GunplayGameInstance = UGunplayGameInstance::GetInstance())
	{
		if (GunplayGameInstance->GetPlayerName().IsEmpty())
		{
			if (UDialogWidget* DialogWidget = GunplayGameInstance->ShowDialog())
			{
				DialogWidget->SetHintText(TEXT("请输入玩家名称"));
				DialogWidget->OnEndInput().AddLambda([this, DialogWidget, GunplayGameInstance]()
				{
					const FText& InputText = DialogWidget->GetInputText();
					if (! InputText.IsEmpty())
					{
						GunplayGameInstance->SetPlayerName(InputText);
						DialogWidget->RemoveFromParent();
						StartLANMode(GunplayGameInstance);
					}
				});
			}
		}
		else
		{
			StartLANMode(GunplayGameInstance);
		}
	}
}

void UGunplayStartWidget::StartDSMode(UGunplayGameInstance* GameInstance) const
{
	GameInstance->SetGunplayMode(EGunplayMode::DSOnline);
	GameInstance->ShowLoading(TEXT("正在进入房间"));
	UGameplayStatics::OpenLevel(this, DSLevel);
}

void UGunplayStartWidget::OnDSClicked()
{
	if (UGunplayGameInstance* GunplayGameInstance = UGunplayGameInstance::GetInstance())
	{
		if (GunplayGameInstance->GetPlayerName().IsEmpty())
		{
			if (UDialogWidget* DialogWidget = GunplayGameInstance->ShowDialog())
			{
				DialogWidget->SetHintText(TEXT("请输入玩家名称"));
				DialogWidget->OnEndInput().AddLambda([this, DialogWidget, GunplayGameInstance]()
				{
					const FText& InputText = DialogWidget->GetInputText();
					if (! InputText.IsEmpty())
					{
						GunplayGameInstance->SetPlayerName(InputText);
						DialogWidget->RemoveFromParent();
						StartDSMode(GunplayGameInstance);
					}
				});
			}
		}
		else
		{
			StartDSMode(GunplayGameInstance);
		}
	}
}
