// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Holding.h"
#include "Hands.generated.h"
/*
 * 没有hold任何holding，空手状态
 * 此状态下可以挥拳
 */
UCLASS()
class GUNPLAY_API AHands : public AHolding
{
	GENERATED_BODY()

public:
	AHands();

	virtual void Use() override;
	virtual void Using(float DeltaTime) override;
	virtual void Used() override;

	virtual void BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hand")
	class UAnimMontage* Montage_Boxing;

	UPROPERTY(EditDefaultsOnly, Category="Hand")
	FName TraceSocket;

	UPROPERTY(EditDefaultsOnly, Category="Hand")
	float HitRadius = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Hand")
	float HitTraceInterval = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category="Hand")
	float ImpulseScale = 100.f;

	UPROPERTY(EditDefaultsOnly, Category="Hand")
	float Damage = 1.f;

	UPROPERTY(EditDefaultsOnly, Category="Hand")
	class USoundBase* PunchSound;

	UFUNCTION(BlueprintNativeEvent, Category="Hand")
	bool AllowHit(class AActor* HitActor);
private:
	UFUNCTION(Server, Reliable)
	void Server_Punch();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Punch();
	
	UFUNCTION()
	void TraceHit();

	UPROPERTY()
	class UAnimInstance* HolderAnimInstance;

	FTimerHandle HitTraceTimerHandle;

	// 存储已经击中的actor，防止一次攻击重复击中
	UPROPERTY()
	TSet<AActor*> AlreadyHitActors;

	FVector LastSocketLocation;

	// 第一次Trace时LastSocketLocation无效
	bool bFirstTraceInOnePunch;
};
