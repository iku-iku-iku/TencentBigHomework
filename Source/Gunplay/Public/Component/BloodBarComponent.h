// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ViewportOrientedWidgetComponent.h"
#include "Components/WidgetComponent.h"
#include "BloodBarComponent.generated.h"

/**
 * 让Actor拥有血条UI
 */
UCLASS()
class GUNPLAY_API UBloodBarComponent : public UViewportOrientedWidgetComponent
{
	GENERATED_BODY()

	UBloodBarComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void RefreshHPRatio() const;

	UPROPERTY()
	class UCharacterStatusComponent* OwnerCharacterStatus;
};
