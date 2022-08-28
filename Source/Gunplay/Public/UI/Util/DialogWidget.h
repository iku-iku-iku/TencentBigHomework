// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"

DECLARE_EVENT(UDialogWidget, FEndInputEvent)

/**
 * 
 */
UCLASS()
class GUNPLAY_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

public:
	FEndInputEvent& OnEndInput() { return EndInputEvent; }

	FText GetInputText() const;

	void SetHintText(const FString& Hint) const;

protected:
	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* InputBox;

	UPROPERTY(meta=(BindWidget))
	class UButton* ConfirmBtn;

	UFUNCTION()
	void OnEndInput(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnConfirm();

	FEndInputEvent EndInputEvent;
};
