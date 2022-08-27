// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "CharacterStatusComponent.generated.h"

DECLARE_EVENT(UCharacterStatusComponent, FCharacterStatusComponentEvent);

/*
 * 为Character提供如下功能：
 * 1. 维护角色的当前状态，而不是玩家的状态，如：HP、Speed等
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API UCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

	virtual void BeginPlay() override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// 角色的具体类型
	UCharacterStatusComponent();


	FORCEINLINE int32 GetHP() const
	{
		return HP;
	}

	FORCEINLINE int32 GetMaxHP() const
	{
		return MaxHP;
	}

	FORCEINLINE int32 GetSpeed() const
	{
		return Speed;
	}

	FORCEINLINE int32 GetAttack() const
	{
		return Attack;
	}

	FORCEINLINE int32 GetDefense() const
	{
		return Defense;
	}

	UFUNCTION(BlueprintPure, Category="Status")
	float GetHPRatio() const { return 1.0f * HP / MaxHP; }

	UFUNCTION(BlueprintCallable, Category="Status")
	void SetHP(const int32 NewValue);

	UFUNCTION(BlueprintCallable, Category="Status")
	void SetMaxHP(const int32 NewValue) { MaxHP = NewValue > 0 ? NewValue : 0; }

	UFUNCTION(BlueprintCallable, Category="Status")
	void SetAttack(const int32 NewValue) { Attack = NewValue > 0 ? NewValue : 0; }

	UFUNCTION(BlueprintCallable, Category="Status")
	void SetSpeed(const int32 NewValue);

	UFUNCTION(BlueprintCallable, Category="Status")
	void SetDefense(const int32 NewValue) { Defense = NewValue > 0 ? NewValue : 0; }

	UFUNCTION(BlueprintCallable, Category="Status")
	void AddHP(const int32 Delta)
	{
		SetHP(HP + Delta);
	}

	UFUNCTION(BlueprintCallable, Category="Status")
	void AddAttack(const int32 Delta) { SetAttack(Attack + Delta); }

	UFUNCTION(BlueprintCallable, Category="Status")
	void AddDefense(const int32 Delta) { SetDefense(Defense + Delta); }

	UFUNCTION(BlueprintCallable, Category="Status")
	void AddSpeed(const int32 Delta) { SetSpeed(Speed + Delta); }


protected:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category="Status")
	int32 HP = 100;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category="Status")
	int32 MaxHP = 100;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category="Status")
	int32 Speed = 400;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category="Status")
	int32 Attack = 10;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category="Status")
	int32 Defense = 5;

private:
	UPROPERTY()
	class AGunplayCharacter* CharacterOwner;


	UPROPERTY()
	class UCharacterMovementComponent* PlayerMovementComponent;

	FCharacterStatusComponentEvent HPZeroEvent;

public:
	FORCEINLINE FCharacterStatusComponentEvent& OnHPZero() { return HPZeroEvent; }
};
