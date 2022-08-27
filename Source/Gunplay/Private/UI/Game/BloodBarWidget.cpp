// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/BloodBarWidget.h"

#include "Components/ProgressBar.h"

void UBloodBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BloodBar)
	{
		BloodBar->PercentDelegate.BindDynamic(this, &UBloodBarWidget::GetHPRatio);
	}
}
