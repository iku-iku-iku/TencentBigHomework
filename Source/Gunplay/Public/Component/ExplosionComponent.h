// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interface/BeHitInterface.h"
#include "ExplosionComponent.generated.h"

/*
 * 引发爆炸的组件
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API UExplosionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UExplosionComponent();

	UFUNCTION(Server, Reliable)
	void Server_Explode(FHitInfo InHitInfo);

protected:
	// 径向力
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Explosio")
	class URadialForceComponent* RadialForceComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Explosio")
	class USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Explosio")
	class UParticleSystem* PS_Explosion;

private:
	UFUNCTION(NetMulticast, Reliable)
	void Multi_Explode();
};
