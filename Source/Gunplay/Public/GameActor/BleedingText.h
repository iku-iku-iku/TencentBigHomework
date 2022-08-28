// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BleedingText.generated.h"

UCLASS()
class GUNPLAY_API ABleedingText : public AActor
{
	GENERATED_BODY()
	
public:	
	ABleedingText();

	UPROPERTY(EditDefaultsOnly)
	class UViewportOrientedWidgetComponent* BleedingTextComponent;

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShowBleeding(const FVector& Location, const int32 BleedingNum);

	void SetHidden();

private:
	bool bShowing;

	float ShowingTimer;
	
	UPROPERTY(EditDefaultsOnly, Category="Bleeding")
	float PostStayTime = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, Category="Bleeding")
	float TransitionTime = .5f;
	
	// 模拟字体大小变化随时间变化

	UPROPERTY(EditDefaultsOnly, Category="Bleeding")
	float InitialFontSize;

	UPROPERTY(EditDefaultsOnly, Category="Bleeding")
	float MaxFontSize;

	// 将fontsize模拟成连续值
	float SimulatingFontSize;

	// 每秒fontsize的变化
	float FontSizeDeltaPerSecond;
	
	UPROPERTY()
	class UBleedingTextWidget* BleedingTextWidget;
};
