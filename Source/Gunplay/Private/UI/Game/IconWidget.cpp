// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/IconWidget.h"

#include "Components/Image.h"


FSlateBrush UIconWidget::GetBrush()
{
	FSlateBrush SlateBrush;
	SlateBrush.SetResourceObject(Image);
	SlateBrush.TintColor = TintColor;
	return SlateBrush;
}

void UIconWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


	if (IconImage)
	{
		IconImage->BrushDelegate.BindDynamic(this, &UIconWidget::GetBrush);
	}
}
