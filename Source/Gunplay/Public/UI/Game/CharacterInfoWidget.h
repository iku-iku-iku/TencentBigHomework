// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterInfoWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 角色的基本信息，如HP、Speed
 */
UCLASS()
class GUNPLAY_API UCharacterInfoWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HPBar;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HPText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SpeedText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AttackText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DefenseText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HoldingNameText;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HoldingCapacityText;
private:

	UFUNCTION(Category="Info")
	float GetHPRatio();

	UFUNCTION(Category="Info")
	FText GetHPRatioText();

	UFUNCTION(Category="Info")
	FText GetSpeedText();
	
	UFUNCTION(Category="Info")
	FText GetAttackText();
	
	UFUNCTION(Category="Info")
	FText GetDefenseText();

	UFUNCTION(Category="Info")
	FText GetHoldingText();

	UFUNCTION(Category="Info")
	FText GetHoldingCapacityText();
};
