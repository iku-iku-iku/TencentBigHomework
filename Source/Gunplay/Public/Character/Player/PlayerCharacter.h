// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GunplayCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 玩家操控的角色
 * 拥有Camera
 */
UCLASS()
class GUNPLAY_API APlayerCharacter : public AGunplayCharacter
{
	GENERATED_BODY()

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	APlayerCharacter();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintPure, Category="Player")
	class AOnlinePlayerState* GetState() const;

	virtual EGunplayCharacterType GetType() const override { return EGunplayCharacterType::Player; }

	class AGunplayPlayerController* GetPlayerController() const;

protected:
	// 出生时携带的手，手可以出拳
	UPROPERTY(EditDefaultsOnly, Category="Player")
	TSubclassOf<class AHands> HandClass;

	// 出生时携带的枪，设为空则表示出生时不带枪
	UPROPERTY(EditDefaultsOnly, Category="Player")
	TSubclassOf<class AGun> GunClass;

	// 瞄准的音效
	UPROPERTY(EditDefaultsOnly, Category="Player")
	class USoundBase* AimSound;

	void LookUp(float Val);

	void Turn(float Val);

	void MobileLookUp(float Val);

	void MobileTurn(float Val);

	void Aim();

	void UnAim();

	virtual void BeKilledBy(const AController* Killer) override;

private:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	FORCEINLINE bool HasRotationInput() const
	{
		return abs(YawInput) > 1e-5f || abs(PitchInput) > 1e-5f;
	}

	// 等Yaw和Pitch都输入完成再处理
	uint8 InputCount;

	void SetCharacterRotationWithInput();

	void SetOrientation();

	void StartRotationInput();

	float HorizontalOrientation;

	float VerticalOrientation;

	// 基准旋转
	FRotator BaseRotation;

	float BaseYawInput;
	float BasePitchInput;

	float YawInput = 0.f;
	float PitchInput = 0.f;

	// 玩家开始转向
	bool bRotating;
};
