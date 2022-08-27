// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/BloodBarComponent.h"
#include "Component/CharacterStatusComponent.h"
#include "Character/GunplayCharacter.h"
#include "UI/Game/BloodBarWidget.h"

UBloodBarComponent::UBloodBarComponent()
{
	DrawSize = {100, 10};
	Pivot = {0.5f, 11.f};
}

void UBloodBarComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(GetOwner()))
	{
		OwnerCharacterStatus = GunplayCharacter->GetStatus();
	}
}

void UBloodBarComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RefreshHPRatio();
}


void UBloodBarComponent::RefreshHPRatio() const
{
	if (UBloodBarWidget* BloodBarWidget = Cast<UBloodBarWidget>(GetWidget()))
	{
		if (OwnerCharacterStatus)
		{
			BloodBarWidget->SetHPRatio(OwnerCharacterStatus->GetHPRatio());
		}
	}
}
