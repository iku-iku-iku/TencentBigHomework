// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IconWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UIconWidget : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	FSlateBrush GetBrush();

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	class UImage* IconImage;

	UPROPERTY()
	UTexture* Image;

	UPROPERTY()
	FLinearColor TintColor;

public:
	void SetIconImage(UTexture* NewValue) { Image = NewValue; }
	FORCEINLINE void SetTintColor(const FLinearColor NewValue) { TintColor = NewValue; }
};
