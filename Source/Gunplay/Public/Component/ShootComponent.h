// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"

/*
 * 提供射击功能
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShootComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE float GetShootRange() const { return ShootRange; }

	FORCEINLINE float GetBaseShootForce() const { return BaseShootForce; }

	FORCEINLINE float GetShootInterval() const { return ShootInterval; }
	bool ShootDetect(const FVector& Start, const FVector& End, FHitResult& OutHit, const ECollisionChannel ShootChannel,
	                 const AActor* IgnoredActor = nullptr) const;

	void GetPlayerShootLine(FVector& Start, FVector& End, const APlayerCharacter* PlayerCharacter) const;
	void GetEnemyShootLine(FVector& Start, FVector& End, const AEnemyCharacter* EnemyCharacter) const;
	void Shoot(const class AGunplayCharacter* Shooter);

	void Shooting(const AGunplayCharacter* Shooter);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Shoot")
	float ShootRange = 5000.f;

	// 冲击力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	float BaseShootForce = 100000.f;

	// 射出两发子弹之间的间隔
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	float ShootInterval = 0.1f;

private:
	UFUNCTION(Server, Reliable)
	void Server_Shoot(const FHitResult& HitResult);

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Shoot(const FHitResult& HitResult);

	float ShootTimer = 0;
};
