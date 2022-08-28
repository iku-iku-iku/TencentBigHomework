// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_KeepDistance.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UEnvQueryTest_KeepDistance : public UEnvQueryTest
{
	GENERATED_BODY()

	explicit UEnvQueryTest_KeepDistance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category=Distance)
	float KeepingDistance = 800.f;

	UPROPERTY(EditDefaultsOnly, Category=Distance)
	float Deviation = 100.f;
	/** context */
	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> DistanceTo;

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;

	virtual FText GetDescriptionDetails() const override;
};
