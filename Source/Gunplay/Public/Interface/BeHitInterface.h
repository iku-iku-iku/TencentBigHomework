// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BeHitInterface.generated.h"

USTRUCT(BlueprintType)
struct FHitInfo
{
	GENERATED_BODY()
	UPROPERTY()
	class AController* Hitter;

	UPROPERTY()
	class AGunplayCharacter* HitterCharacter;

	UPROPERTY()
	FVector Impulse;

	UPROPERTY()
	FVector HitLocation;

	UPROPERTY()
	int32 Damage;

	FHitInfo(AController* Hitter, AGunplayCharacter* HitterCharacter, const FVector& Impulse,
	         const FVector& HitLocation, const int32 Damage)
		: Hitter(Hitter),
		  HitterCharacter(HitterCharacter),
		  Impulse(Impulse),
		  HitLocation(HitLocation),
		  Damage(Damage)
	{
	}

	FHitInfo(): FHitInfo(nullptr, nullptr, FVector(0), FVector(0), 0)
	{
	}
};

UINTERFACE(MinimalAPI)
class UBeHitInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */
class GUNPLAY_API IBeHitInterface
{
	GENERATED_BODY()

public:
	virtual void BeHit(const FHitInfo& HitInfo) = 0;
};
