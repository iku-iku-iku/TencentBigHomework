// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Holding/Gun.h"
#include "MainCharacterGun.generated.h"

/**
 * 主角用枪
 * 具有手电筒
 */
UCLASS()
class GUNPLAY_API AMainCharacterGun : public AGun
{
	GENERATED_BODY()

public:
	AMainCharacterGun();

	virtual void BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpotLightComponent* SpotLightComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* SpotLightRoot;
};
