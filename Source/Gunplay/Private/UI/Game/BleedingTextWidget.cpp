// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/BleedingTextWidget.h"

#include "Components/TextBlock.h"

void UBleedingTextWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (BleedingTextBlock)
	{
		BleedingTextBlock->SetJustification(ETextJustify::Center);
	}
}

void UBleedingTextWidget::SetBleeding(const int32 Num) const
{
	if (BleedingTextBlock)
	{
		BleedingTextBlock->SetText(FText::FromString(FString::FromInt(Num)));
	}
}

void UBleedingTextWidget::SetFontSize(const int32 NewValue) const
{
	if (BleedingTextBlock)
	{
		FSlateFontInfo SlateFontInfo = BleedingTextBlock->Font;
		SlateFontInfo.Size = NewValue;
		BleedingTextBlock->SetFont(SlateFontInfo);
	}
}

int32 UBleedingTextWidget::GetFontSize() const
{
	return BleedingTextBlock ? BleedingTextBlock->Font.Size : 0;
}
