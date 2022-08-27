// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/UserDefinedStruct.h"
#include "MapItemStruct.generated.h"

/**
 * 
 */
USTRUCT()
struct GUNPLAY_API FMapItemStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Table")
	FText MapName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Table")
	FString Map;
};
