// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "Components/ActorComponent.h"
#include "ProjectileComponent.generated.h"


/*
 * 抛掷物
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API UProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UProjectileComponent();

	void Project(const class AGunplayCharacter* Projector);

	void Montage_StartProject(const class AGunplayCharacter* Projector) const;
	void Montage_EndProject(const class AGunplayCharacter* Projector) const;

	FORCEINLINE void SetProjectForce(const float NewValue) { ProjectForce = NewValue; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	float ProjectForce = 5000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	float ProjectHeightScale = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	float ProjectStartOffset = 30.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	UAnimMontage* Montage_ThrowGrenade;

private:
	uint8 bHasBeenProjected : 1;
};
