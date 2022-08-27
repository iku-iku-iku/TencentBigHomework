// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AnimationComponent.generated.h"

/*
 * 封装需要同步的动画状态
 * 这些状态会优先在本地改变
 * 只有状态发生改变，才会调用ServerRPC，在Server端修改状态并同步到所有客户端
 * 所有客户端的动画蓝图都能通过变量同步接受到变化后的状态
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAnimationComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE bool IsAiming() const { return bAiming; }
	void SetAiming(bool NewValue);

	FORCEINLINE bool IsInAir() const { return bInAir; }
	void SetInAir(const bool NewValue);

	FORCEINLINE bool IsShooting() const { return bShooting; }
	void SetIsShooting(const bool NewValue);

	FORCEINLINE bool IsWantToJump() const { return bWantToJump; }
	void SetWantToJump(const bool NewValue);

	FORCEINLINE bool ConsumeWanToJump()
	{
		if (bWantToJump)
		{
			bWantToJump = false;
			return true;
		}
		return false;
	}

	FORCEINLINE float GetHorizontalOrientation() const { return HorizontalOrientation; }
	void SetHorizontalOrientation(float NewValue);

	FORCEINLINE float GetVerticalOrientation() const { return VerticalOrientation; }
	void SetVerticalOrientation(float NewValue);

private:
	UFUNCTION(Server, Reliable)
	void Server_SetVerticalOrientation(float NewValue);

	UFUNCTION(Server, Reliable)
	void Server_SetHorizontalOrientation(float NewValue);

	UFUNCTION(Server, Reliable)
	void Server_SetIsShooting(const bool NewValue);

	UFUNCTION(Server, Reliable)
	void Server_SetInAir(const bool NewValue);

	UFUNCTION(Server, Reliable)
	void Server_SetAiming(bool NewValue);

	UFUNCTION(Server, Reliable)
	void Server_SetWantToJump(const bool NewValue);

	UPROPERTY(Replicated)
	uint8 bWantToJump : 1;

	UPROPERTY(Replicated)
	uint8 bInAir : 1;

	UPROPERTY(Replicated)
	uint8 bShooting : 1;

	UPROPERTY(Replicated)
	uint8 bAiming : 1;

	UPROPERTY(Replicated)
	float HorizontalOrientation;

	UPROPERTY(Replicated)
	float VerticalOrientation;
};
