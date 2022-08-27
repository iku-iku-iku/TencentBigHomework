// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Queue.h"
#include "GameActor/BleedingText.h"
#include "BleedingTextManager.generated.h"

/**
 * 管理飙血伤害文字
 */
UCLASS(Blueprintable)
class GUNPLAY_API UBleedingTextManager : public UObject
{
	GENERATED_BODY()

public:
	void SpawnBleedingTextAt(const FVector& Location, const int32 BleedingNum);

	void AddToPool(ABleedingText* BleedingText);

	static UBleedingTextManager* GetInstance();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Bleeding")
	TSubclassOf<ABleedingText> BleedingTextClass;
private:
	UPROPERTY()
	TArray<ABleedingText*> BleedingTextPool;

	UPROPERTY(EditDefaultsOnly, Category="Bleeding")
	float RandomDeviation = 50;

	void FillBleedingText();	
};

