// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/WaveWidget.h"
#include "Components/TextBlock.h"
#include "Game/Solitary/ExtremeSurvivalGameMode.h"
#include "Kismet/GameplayStatics.h"

namespace
{
	UWaveWidget* WaveWidgetInstance;
}

void UWaveWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	WaveText->TextDelegate.BindDynamic(this, &UWaveWidget::GetWaveText);

	if (AExtremeSurvivalGameMode* ExtremeSurvivalGameMode = Cast<AExtremeSurvivalGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		ExtremeSurvivalGameMode->OnStartNextWave().AddUObject(this, &UWaveWidget::SetWaveCount);
	}
}

void UWaveWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WaveWidgetInstance = this;
}

UWaveWidget* UWaveWidget::GetInstance()
{
	return WaveWidgetInstance;
}

FText UWaveWidget::GetWaveText()
{
	return FText::FromString(FString::Printf(TEXT("第%d波"), WaveCount));
}
