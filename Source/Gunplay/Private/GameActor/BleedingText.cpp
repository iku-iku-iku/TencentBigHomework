// Copyright iku-iku-iku,. All Rights Reserved.


#include "GameActor/BleedingText.h"

#include "Component/ViewportOrientedWidgetComponent.h"
#include "Manager/BleedingTextManager.h"
#include "UI/Game/BleedingTextWidget.h"

ABleedingText::ABleedingText()
{
	PrimaryActorTick.bCanEverTick = true;

	BleedingTextComponent = CreateDefaultSubobject<UViewportOrientedWidgetComponent>(TEXT("Bleeding Text"));

	RootComponent = BleedingTextComponent;
}

void ABleedingText::BeginPlay()
{
	Super::BeginPlay();
	BleedingTextWidget = Cast<UBleedingTextWidget>(BleedingTextComponent->GetWidget());
}

void ABleedingText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bShowing) { return; }

	ShowingTimer -= DeltaTime;
	if (ShowingTimer > 0)
	{
		if (BleedingTextWidget)
		{
			SimulatingFontSize += FontSizeDeltaPerSecond * DeltaTime;
			BleedingTextWidget->SetFontSize(SimulatingFontSize);
		}
	}

	if (ShowingTimer < -PostStayTime)
	{
		UBleedingTextManager::GetInstance()->AddToPool(this);
	}
}

void ABleedingText::ShowBleeding(const FVector& Location, const int32 BleedingNum)
{
	SetActorHiddenInGame(false);
	bShowing = true;

	FontSizeDeltaPerSecond = (MaxFontSize - InitialFontSize) / TransitionTime;
	ShowingTimer = TransitionTime;

	if (BleedingTextWidget)
	{
		SimulatingFontSize = InitialFontSize;
		BleedingTextWidget->SetFontSize(InitialFontSize);
		BleedingTextWidget->SetBleeding(BleedingNum);
	}

	this->SetActorLocation(Location);
}

void ABleedingText::SetHidden()
{
	SetActorHiddenInGame(true);
	bShowing = false;
}
