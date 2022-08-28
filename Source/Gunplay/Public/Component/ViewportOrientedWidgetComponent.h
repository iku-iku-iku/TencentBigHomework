// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ViewportOrientedWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UViewportOrientedWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UViewportOrientedWidgetComponent();

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void RotateToFaceCamera();
};
