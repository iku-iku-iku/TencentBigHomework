// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AdsorbInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAdsorbInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GUNPLAY_API IAdsorbInterface
{
	GENERATED_BODY()

public:
	virtual bool CanAdsorb() const { return true; }
};
