// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_CanShoot.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UEnvQueryTest_CanShoot : public UEnvQueryTest
{
	GENERATED_BODY()

	explicit UEnvQueryTest_CanShoot(const FObjectInitializer& ObjectInitializer);

	/** context */
	UPROPERTY(EditDefaultsOnly, Category="Shoot")
	TSubclassOf<UEnvQueryContext> Target;

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;

	virtual FText GetDescriptionDetails() const override;
};
