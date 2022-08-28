// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_Attack.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UBTT_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTT_Attack();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual FString GetStaticDescription() const override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


protected:
	UPROPERTY(EditAnywhere, Category="Enemy")
	FBlackboardKeySelector AttackCoolDownTimer;

	// 攻击冷却时看作什么结果
	UPROPERTY(EditAnywhere, Category="Enemy")
	TEnumAsByte<EBTNodeResult::Type> CoolDownAttackResult = EBTNodeResult::Succeeded;

	// 是否由Controller提供Duration
	UPROPERTY(EditAnywhere, Category="Enemy")
	bool bDurationProvideByController = false;

	// TODO 根据bDurationProvidedByController的开启与否显示启用该项
	UPROPERTY(EditAnywhere, Category="Enemy")
	float Duration = 0.2f;

	FTimerHandle AttackTimerHandle;

	bool bFinish;
};
