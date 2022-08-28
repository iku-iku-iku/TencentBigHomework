// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Component/ViewportOrientedWidgetComponent.h"
#include "IconComponent.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UIconComponent : public UViewportOrientedWidgetComponent
{
	GENERATED_BODY()

	UIconComponent();

	virtual void BeginPlay() override;

	UFUNCTION()
	void InitMaterial();
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Icon")
	UTexture* Icon;

	UPROPERTY(EditDefaultsOnly, Category="Icon")
	float Lightness = 10.f;
};
