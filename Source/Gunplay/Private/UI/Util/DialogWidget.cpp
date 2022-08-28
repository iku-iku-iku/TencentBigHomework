// Copyright iku-iku-iku,. All Rights Reserved.

#include "UI/Util/DialogWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void UDialogWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InputBox->OnTextCommitted.AddDynamic(this, &UDialogWidget::OnEndInput);
	ConfirmBtn->OnClicked.AddDynamic(this, &UDialogWidget::OnConfirm);
}

FText UDialogWidget::GetInputText() const
{
	return InputBox->GetText();
}

void UDialogWidget::SetHintText(const FString& Hint) const
{
	InputBox->SetHintText(FText::FromString(Hint));
}

void UDialogWidget::OnEndInput(const FText& Text, ETextCommit::Type CommitMethod)
{
	EndInputEvent.Broadcast();
}

void UDialogWidget::OnConfirm()
{
	EndInputEvent.Broadcast();
}
