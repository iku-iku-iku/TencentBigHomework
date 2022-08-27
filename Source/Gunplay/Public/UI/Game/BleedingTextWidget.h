// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BleedingTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBleedingTextWidget : public UUserWidget
{
	GENERATED_BODY()


	virtual void NativeOnInitialized() override;
protected:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* BleedingTextBlock;

	

public:
	void SetBleeding(const int32 Num) const;

	void SetFontSize(const int32 NewValue) const;
	
	int32 GetFontSize() const;
};
