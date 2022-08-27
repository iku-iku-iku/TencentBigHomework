// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/ViewportOrientedWidgetComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UViewportOrientedWidgetComponent::UViewportOrientedWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UViewportOrientedWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	RotateToFaceCamera();
}

void UViewportOrientedWidgetComponent::RotateToFaceCamera()
{
	const FVector SelfLocation = GetComponentLocation();

	if (const APlayerCameraManager* PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
	{
		const FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
		const FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(SelfLocation, CameraLocation);
		SetWorldRotation(Rotator);
	}
}
