// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "UObject/Interface.h"
#include "ShootInterface.generated.h"

UINTERFACE()
class UShootInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 实现改接口以提供具体的射击逻辑
 * 要具有射击功能还需要具有ShootComponent
 */
class GUNPLAY_API IShootInterface
{
	GENERATED_BODY()

public:
	// Server上进行的射击结算
	virtual bool Server_Shoot(const FHitResult& HitResult) = 0;

	// 多播射击效果
	virtual void Multi_ShootEffect(const FHitResult& HitResult) = 0;
};
