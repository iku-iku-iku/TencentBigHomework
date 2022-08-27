// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaveWidget.generated.h"

class UTextBlock;

/**
 * 
 */


UCLASS()
class GUNPLAY_API UWaveWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
public:
	FORCEINLINE void SetWaveCount(const int32 NewValue) { WaveCount = NewValue; }
	FORCEINLINE int32 GetWaveCount() const { return WaveCount; }

	static UWaveWidget* GetInstance();

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* WaveText;
private:
	UFUNCTION()
	FText GetWaveText();


	int32 WaveCount;
};

