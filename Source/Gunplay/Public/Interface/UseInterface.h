// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UseInterface.generated.h"

UINTERFACE(MinimalAPI)
class UUseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Actor能被使用的接口，如开枪、抛掷手雷等
 */
class GUNPLAY_API IUseInterface
{
	GENERATED_BODY()

public:
	// 使用一次
	virtual void Use() = 0;

	// 使用中
	virtual void Using(float DeltaTime) = 0;

	// 使用完
	virtual void Used() = 0;
};
