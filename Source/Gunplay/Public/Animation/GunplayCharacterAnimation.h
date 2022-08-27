// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GunplayCharacterAnimation.generated.h"

/**
 * 角色的动画蓝图
 */
UCLASS(Transient, BlueprintType, Blueprintable, HideCategories=(AnimInstance))
class GUNPLAY_API UGunplayCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION()
	void AnimNotify_ThrowGrenade() const;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	class AGunplayCharacter* OwningCharacter;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	FVector BarrelLocation;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	float Direction;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	float TurnRate;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	float VerticalOrientation;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	float HorizontalOrientation;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	uint8 bHoldingGun : 1;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	uint8 bJump : 1;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	uint8 bInAir : 1;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	uint8 bTurnRight : 1;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	uint8 bIsShooting : 1;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	uint8 bIsStatic : 1;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	uint8 bIsAiming : 1;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	FVector LFootEffectorLocation;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	FVector RFootEffectorLocation;

	UPROPERTY(BlueprintReadOnly, Category="Anim")
	FVector HipTranslation;

	UPROPERTY(EditDefaultsOnly, Category="Anim")
	float StaticTolerance = 10.f;
};
