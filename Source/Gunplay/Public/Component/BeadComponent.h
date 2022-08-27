// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeadComponent.generated.h"

/*
 * 具有UBeadComponent的Holding可以让屏幕上出现一个准星UI
 * 这个准星UI的半径相关参数可以在此组件中设置
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API UBeadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBeadComponent();

	// 射击时使得准星偏移
	void BeadShoot()
	{
		ShootOffset += GetOffsetPerShoot();
		ShootOffset = FMath::Min(ShootOffset, GetMaxRadius() - GetBaseRadius());
	}
	
	// Bead拉取Radius数据
	float GetBaseRadius() const;

	// 获取每次射击的偏移量
	FORCEINLINE float GetOffsetPerShoot() const { return BeadOffsetPerShoot; }

	// 获取最大半径
	FORCEINLINE float GetMaxRadius() const { return MaxBeadRadius; }

	// Bead使用完增加量后重置Offset
	float ConsumeShootOffset()
	{
		const float Tmp = ShootOffset;
		ShootOffset = 0;
		return Tmp;
	}
	
	static void GetBeadRandPoint(FVector& WorldLocation, FVector& WorldDirection);
	
protected:
	// 基础准星半径
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float BaseBeadRadius = 20.f;

	// 瞄准时的准星半径
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float AimBaseBeadRadius = 0.f;

	// 每次射击准星增加的偏移量
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float BeadOffsetPerShoot = 20.f;

	// 最大准星半径
	UPROPERTY(EditDefaultsOnly, Category="Bead")
	float MaxBeadRadius = 100.f;

	UPROPERTY(EditDefaultsOnly, Category="Bead")
	TSubclassOf<class UBeadWidget> BeadWidgetClass;

private:
	float ShootOffset = 0.f;
};
