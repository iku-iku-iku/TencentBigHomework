#pragma once

#include "CoreMinimal.h"
#include "Holding.h"
#include "Grenade.generated.h"

UCLASS()
class GUNPLAY_API AGrenade : public AHolding
{
	GENERATED_BODY()

	AGrenade();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class UPickupComponent* PickupComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class UProjectileComponent* ProjectileComponent;
public:
	virtual void Use() override;

	virtual void Using(float DeltaTime) override;

	virtual void Used() override;

	virtual void BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter) override;

	void ThrowGrenade();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	float ExplodeDelayTime = 1.0f;

	// 伤害 = DamageScale * Attack
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Grenade")
	float DamageScale = 10.f;

	// 可以被spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grenade")
	class USpawnComponent* SpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grenade")
	class UExplosionComponent* ExplosionComponent;

	UFUNCTION(Server, Reliable)
	void Server_ThrowMontage(bool bStart);

	UFUNCTION(NetMulticast, Reliable)
	void Multi_ThrowMontage(bool bStart);

	UFUNCTION(Server, Reliable)
	void Server_ThrowGrenade();


	UPROPERTY(EditDefaultsOnly, Category="Grenade")
	FName AttachedSocketName = TEXT("GrenadeSocket");

private:
	UFUNCTION(Server, Reliable)
	void Server_Explode();
};
