// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/SingletonWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UMenuWidget : public USingletonWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta=(BindWidget))
	class USlider* TurnSensitivity;
	
	UPROPERTY(meta=(BindWidget))
	class USlider* LookUpSensitivity;

	UFUNCTION(BlueprintCallable, Category="Menu")
	void SetTurnSensitivity(float Value);

	UFUNCTION(BlueprintCallable, Category="Menu")
	void SetLookUpSensitivity(float Value);

	UPROPERTY(EditDefaultsOnly, Category="Menu")
	TArray<FName> TurnAxisName;
	
	UPROPERTY(EditDefaultsOnly, Category="Menu")
	TArray<FName> LookUpAxisName;
};
