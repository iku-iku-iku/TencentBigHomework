// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoldComponent.generated.h"

DECLARE_EVENT(UHoldingComponent, FHoldingEvent)

/*
 * 能够让Character具有以下功能
 * 1. 拥有 Holding
 * 2. 切换 Holding 显示
 * 3. 使用 Holding : Use/Using/Used，分别对应“按下”、“按着”、“松开”使用键
 */
// Holding 能够被 “Use”, 则需要实现IUseInterfaceType接口
// IUseInterfaceType 需要包含 Use/Using/Used，分别对应“按下”、“按着”、“松开”使用键
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API UHoldComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	UHoldComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 真正切换Holding的函数
	void SwitchShowingHolding(int32 OldIndex, int32 NewIndex);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
private:
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentHoldingIndex)
	int32 CurrentHoldingIndex = -1;

	UPROPERTY(Replicated)
	int32 OldHoldingIndex = -1;

	// 存储所有Holding，用于状态同步
	UPROPERTY(ReplicatedUsing=OnRep_Holdings)
	TArray<class AActor*> Rep_Holdings;

	UFUNCTION()
	void OnRep_Holdings();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Holding")
	bool bSwitchToWhenPickup = true;

	// 手上拿着的东西，可以切换
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Holding")
	TArray<class AActor*> HoldingSlots;

private:

	UFUNCTION(Server, Reliable)
	void Server_SetCurrentHoldingIndex(const int32 NewIndex);

	UFUNCTION()
	void OnRep_CurrentHoldingIndex();

public:
	void SwitchHoldingWithAxis(float Value);

	UFUNCTION(BlueprintCallable, Category="Holding")
	void UseCurrentHolding();

	UFUNCTION(BlueprintCallable, Category="Holding")
	void UsingCurrentHolding(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category="Holding")
	void UsedCurrentHolding();

	UFUNCTION(BlueprintPure, Category="Holding")
	int32 GetHoldingNum(const TSubclassOf<class AActor> HoldingClass) const;

	UFUNCTION(BlueprintCallable, Category="Holding")
	void AddHolding(AActor* Holding);

	UFUNCTION(BlueprintCallable, Category="Holding")
	void RemoveHolding(AActor* Holding);

	UFUNCTION(BlueprintPure, Category="Holding")
	class AActor* GetCurrentHolding() const;

	FORCEINLINE TArray<class AActor*> GetAllHoldings() { return Rep_Holdings; }

	FORCEINLINE void SetCurrentHoldingIndex(const int32 NewIndex)
	{
		Server_SetCurrentHoldingIndex(NewIndex);
	}

	UFUNCTION(BlueprintCallable, Category="Holding")
	void SwitchHoldingRight();

	UFUNCTION(BlueprintCallable, Category="Holding")
	void SwitchHoldingLeft();

	UFUNCTION(BlueprintCallable, Category="Holding")
	void SwitchHolding(TSubclassOf<AActor> TargetClass);

	UFUNCTION(BlueprintPure, Category="Holding")
	class AActor* FindHolding(UClass* HoldingClass);

	FORCEINLINE FHoldingEvent& OnSwitchHolding() { return SwitchHoldingEvent; }


private:
	bool bUsingHolding = false;

	FHoldingEvent SwitchHoldingEvent;

	UPROPERTY(ReplicatedUsing=OnRep_CurrentHoldingIndex)
	int32 CurrentIndexId;
};
