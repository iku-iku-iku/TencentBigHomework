// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Player/PlayerCharacter.h"
#include "UI/SingletonWidget.h"
#include "BeadWidget.generated.h"

class UTextBlock;
/**
 * 准星
 * 射击时变大
 * 在准星范围内随机射击
 */
UCLASS()
class GUNPLAY_API UBeadWidget : public USingletonWidget
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;

	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LeftBead;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* RightBead;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* UpBead;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DownBead;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CenterBead;


public:
	void GetRandomPoint(FVector& WorldLocation, FVector& WorldDirection);

	void Coord2WorldSpace(const FVector2D& Coord, FVector& WorldLocation, FVector& WorldDirection,
	                      UWidget* Widget) const;

	FORCEINLINE void SetBaseRadius(const float NewValue)
	{
		// !!! BaseRadius用于编辑器调节，对外透明，实际设置的是BaseOffset !!!
		BaseOffset = NewValue;
		SetAllBeadPosition();
	}

	FORCEINLINE void AddShootOffset(const float NewValue)
	{
		ShootOffset += NewValue;
		SetAllBeadPosition();
	}

	// BaseRadius对外透明
	FORCEINLINE float GetRadius() const { return BaseOffset + ShootOffset; }

	FORCEINLINE void ShowBead()
	{
		SetRenderOpacity(1.f);
	}

	FORCEINLINE void HideBead()
	{
		SetRenderOpacity(0.f);
	}

	UFUNCTION(BlueprintCallable, Category="Bead")
	void SetAdsorbEnable(bool bEnable);

private:
	FORCEINLINE float GetTotalRadius() const { return BaseRadius + BaseOffset + ShootOffset; }
	// 用于编辑器调节基础半径
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float BaseRadius = 30.f;

	// 基础半径上的增加值
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float BaseOffset = 0.f;

	// 射击时增加的半径
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float ShootOffset = 0.f;

	// 每秒收缩的速度，ShootOffset减到0则不再收缩
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float ShrinkRate = 100.f;

	// 吸附时的检测偏移半径
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float AdsorbRadiusOffset = 50.f;

	// 在此半径范围内能够射击到目标则不会吸附
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float AdsorbThreshold = 30.f;

	void SetAllBeadPosition() const;

	void SetBeadPosition(class UWidget* Widget, const FVector2D& Dir) const;

	void AutoAdsorb();

	bool CanAdsorb(FVector2D Coord) const;

	void UpdateBeadStatus();

	UPROPERTY()
	const class APlayerCharacter* OwnerPlayerCharacter;

private:
	FVector2D InitialCenterTranslation;

	bool bEnableAdsorb;

	float GetPureRadius() {return BaseRadius + BaseOffset;}
};
