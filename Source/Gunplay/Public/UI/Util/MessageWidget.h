// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UMessageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void InjectMessage(const FText& Value) {Message = Value;}
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn="true"))
	FText Message;
};
