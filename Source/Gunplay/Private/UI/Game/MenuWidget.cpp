// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/MenuWidget.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

#include "Components/Slider.h"
#include "Game/GunplayPlayerController.h"

void UMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TurnSensitivity->OnValueChanged.AddDynamic(this, &UMenuWidget::SetTurnSensitivity);
	LookUpSensitivity->OnValueChanged.AddDynamic(this, &UMenuWidget::SetLookUpSensitivity);

	SetTurnSensitivity(TurnSensitivity->Value);
	SetLookUpSensitivity(LookUpSensitivity->Value);
}

void UMenuWidget::SetTurnSensitivity(const float Value)
{
	if (AGunplayPlayerController* PlayerController = Cast<AGunplayPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0)))
	{
		PlayerController->SetTurnSensitivity(Value);
	}
}

void UMenuWidget::SetLookUpSensitivity(float Value)
{
	if (AGunplayPlayerController* PlayerController = Cast<AGunplayPlayerController>(
		UGameplayStatics::GetPlayerController(this, 0)))
	{
		PlayerController->SetLookUpSensitivity(Value);
	}
}
