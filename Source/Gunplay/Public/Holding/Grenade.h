#pragma once

#include "CoreMinimal.h"
#include "Holding.h"
#include "Grenade.generated.h"

UCLASS()
class GUNPLAY_API AGrenade : public AHolding
{
	GENERATED_BODY()

	AGrenade();

<<<<<<< HEAD
protected:
=======
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gun")
	class UParticleSystemComponent* ParticleSystemComponent;

>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class UPickupComponent* PickupComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class UStaticMeshComponent* Mesh;
<<<<<<< HEAD

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class UProjectileComponent* ProjectileComponent;
=======
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
public:
	virtual void Use() override;

	virtual void Using(float DeltaTime) override;

	virtual void Used() override;

	virtual void BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter) override;

	void ThrowGrenade();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
<<<<<<< HEAD
=======
	float BaseThrowForce = 5000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	float ThrowHeightScale = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	float ThrowStartOffset = 30.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
	float ExplodeDelayTime = 1.0f;

	// 伤害 = DamageScale * Attack
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	float DamageScale = 10.f;

<<<<<<< HEAD
=======
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	class USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	class UParticleSystem* PS_Explosion;

	// 径向力
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class URadialForceComponent* RadialForceComponent;

>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
	// 可以被spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class USpawnComponent* SpawnComponent;

<<<<<<< HEAD
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grenade")
	class UExplosionComponent* ExplosionComponent;

=======
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
	UFUNCTION(Server, Reliable)
	void Server_ThrowMontage(bool bStart);

	UFUNCTION(NetMulticast, Reliable)
	void Multi_ThrowMontage(bool bStart);

<<<<<<< HEAD
	UFUNCTION(Server, Reliable)
	void Server_ThrowGrenade();

=======
	// 一段时间后爆炸
	UFUNCTION(Server, Reliable)
	void Explode();

	UFUNCTION(Server, Reliable)
	void Server_ThrowGrenade();

	// 多播特效和音效
	UFUNCTION(NetMulticast, Reliable)
	void Multi_Explode();

	FTimerHandle Server_TimerHandleExplode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	class UAnimMontage* Montage_ThrowGrenade;
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc

	UPROPERTY(EditDefaultsOnly, Category="Grenade")
	FName AttachedSocketName = TEXT("GrenadeSocket");

private:
<<<<<<< HEAD
	UFUNCTION(Server, Reliable)
	void Server_Explode();
=======
	uint8 bHasBeenThrown : 1;
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
};
