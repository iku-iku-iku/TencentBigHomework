// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Util/LoadingWidget.h"

void ULoadingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Timer -= InDeltaTime;
	if (Timer < 0)
	{
		Timer = Interval;
		DotNum = (DotNum + 1) % (MaxDot + 1);
		LoadingMessage = FText::FromString(Message + FString::ChrN(DotNum, TEXT('.')));
	}
}