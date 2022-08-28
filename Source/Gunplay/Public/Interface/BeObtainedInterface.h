// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BeObtainedInterface.generated.h"

UINTERFACE(MinimalAPI)
class UBeObtainedInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief 实现此接口的类可以获得"被获取"的能力
 */
class GUNPLAY_API IBeObtainedInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BeObtainedBy(class AGunplayCharacter* GunplayCharacter);

	virtual void BeObtainedBy_Implementation(class AGunplayCharacter* GunplayCharacter) = 0;
};
