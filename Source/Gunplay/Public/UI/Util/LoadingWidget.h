// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingWidget.generated.h"

/**
 * Loading UI
 */
UCLASS()
class GUNPLAY_API ULoadingWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	FORCEINLINE void InjectMessage(FString NewValue) {Message = NewValue;}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Loading", meta=(ExposeOnSpawn="true"))
	FString Message = TEXT("Loading");

private:
	float Interval = 0.2f;

	int32 MaxDot = 6;
	
	float Timer = 0;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FText LoadingMessage;

	int32 DotNum = 0;
};
