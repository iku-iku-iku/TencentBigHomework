// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BloodBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBloodBarWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

	float HPRatio;

	UFUNCTION()
	float GetHPRatio() { return HPRatio; }

protected:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* BloodBar;

public:
	FORCEINLINE void SetHPRatio(const float NewValue) { HPRatio = NewValue; }
};
