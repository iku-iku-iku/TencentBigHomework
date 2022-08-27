// Copyright iku-iku-iku,. All Rights Reserved.


#include "Holding/MainCharacterGun.h"

#include "Camera/CameraComponent.h"
#include "Character/Player/PlayerCharacter.h"
#include "Component/BeadComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMainCharacterGun::AMainCharacterGun()
{
	SpotLightRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Light"));
	SpotLightRoot->SetupAttachment(RootComponent);
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));

	check(SpotLightComponent != nullptr)
	SpotLightComponent->SetupAttachment(SpotLightRoot);
	SpotLightComponent->bEditableWhenInherited = true;
	SpotLightComponent->SetHiddenInGame(true);
	SpotLightComponent->SetRelativeLocation(FVector(0, 65, 15));
}

void AMainCharacterGun::BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter)
{
	Super::BeObtainedBy_Implementation(GunplayCharacter);

	SpotLightComponent->SetHiddenInGame(false);

	SpotLightComponent->SetLightingChannels(true, true, false);
}
