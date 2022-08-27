// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_Density.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UEnvQueryTest_Density : public UEnvQueryTest
{
	GENERATED_BODY()
	
	explicit UEnvQueryTest_Density(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category="Density")
	float DetectRadius = 100.f;

	/** context */
	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> Ignore;
	
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;

	virtual FText GetDescriptionDetails() const override;
};
