// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/IconComponent.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetSystemLibrary.h"

UIconComponent::UIconComponent()
{
	SetIsReplicatedByDefault(true);
	DrawSize = {50, 50};
}

void UIconComponent::BeginPlay()
{
	Super::BeginPlay();

	const FLatentActionInfo LatentActionInfo(0, FMath::Rand(), TEXT("InitMaterial"), this);
	UKismetSystemLibrary::Delay(this, 0.1f, LatentActionInfo);
}

void UIconComponent::InitMaterial()
{
	if (UMaterialInstanceDynamic* MaterialInstanceDynamic = GetMaterialInstance())
	{
		if (Icon)
		{
			MaterialInstanceDynamic->SetTextureParameterValue(TEXT("Icon"), Icon);
		}
		MaterialInstanceDynamic->SetScalarParameterValue(TEXT("Lightness"), Lightness);
	}
}
