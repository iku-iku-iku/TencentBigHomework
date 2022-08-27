#pragma once

#include "CoreMinimal.h"
#include "Holding.h"
#include "Interface/ShootInterface.h"
#include "Gun.generated.h"

UCLASS()
class GUNPLAY_API AGun : public AHolding, public IShootInterface
{
	GENERATED_BODY()

public:
	AGun();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gun")
	class UShootComponent* ShootComponent;
	// 提供可被拾取功能
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gun")
	class UPickupComponent* PickupComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gun")
	class USkeletalMeshComponent* Mesh;

	// 可以不停被Spawn，保障可以拿到武器
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gun")
	class USpawnComponent* SpawnComponent;

	// 提供准星显示，以及准星偏移
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gun")
	class UBeadComponent* BeadComponent;

	// 子弹特效
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	class UParticleSystem* PS_BulletImpact;

	// 子弹音效
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Gun")
	class USoundBase* Sd_ShootImpact;

	// 伤害 = Attack * DamageScale
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	float DamageScale = 1.0f;

	// 伤害偏移（作用于Scale）
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gun")
	float DamageDeviation = 0.2f;

	// 最大子弹数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gun")
	int32 MaxBulletNum = 20;

	// 当前子弹数
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Gun")
	int32 BulletNum = 20;

	// 爆头伤害倍率
	UPROPERTY(EditDefaultsOnly, Category="Gun")
	float HeadShotDamageRate = 2.f;

	UPROPERTY(EditDefaultsOnly, Category="IK")
	FName AttachedSocketName = TEXT("GunSocket");

	UPROPERTY(EditDefaultsOnly, Category="IK")
	FName BarrelSocketName = TEXT("BarrelSocket");

	UPROPERTY(EditDefaultsOnly, Category="Decal")
	class UMaterial* Mat_BulletHoleDecal;

	UPROPERTY(EditDefaultsOnly, Category="Decal")
	FVector BulletHoleSize = {20.f, 20.f, 20.f};

	UPROPERTY(EditDefaultsOnly, Category="Decal")
	float BulletHoleLifeSpan = 0.f;

	UPROPERTY(EditDefaultsOnly, Category="Decal")
	float FadeScreenSize = 0.f;

public:
	virtual void Use() override
	{
	}

	virtual void Using(float DeltaTime) override;

	virtual void Used() override;

	virtual void BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter) override;

	FORCEINLINE int32 GetBulletNum() const { return BulletNum; }

	FORCEINLINE int32 GetMaxBulletNum() const { return MaxBulletNum; }

	FORCEINLINE void SetMaxBullet(const int32 NewValue) { MaxBulletNum = NewValue; }

	FORCEINLINE void SetBulletNum(const int32 NewValue) { BulletNum = NewValue; }

	UFUNCTION(BlueprintPure, Category="Gun")
	FVector GetBarrelLocation() const;

	FORCEINLINE class UShootComponent* GetShootComponent() const { return ShootComponent; }

private:
	virtual bool Server_Shoot(const FHitResult& HitResult) override;

	// 声音、粒子效果
	virtual void Multi_ShootEffect(const FHitResult& HitResult) override;

	float CalculateDamage(const FHitResult& HitResult) const;
};
