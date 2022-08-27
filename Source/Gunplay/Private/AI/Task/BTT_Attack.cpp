// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Task/BTT_Attack.h"

#include "TimerManager.h"
#include "AI/EnemyAIController.h"
#include "Async/Async.h"
#include "BehaviorTree/BlackboardComponent.h"
<<<<<<< HEAD
#include "Component/HoldComponent.h"
=======
#include "Component/HoldingComponent.h"
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc


UBTT_Attack::UBTT_Attack()
{
	NodeName = TEXT("攻击");
	bCreateNodeInstance = true;
}

void UBTT_Attack::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

FString UBTT_Attack::GetStaticDescription() const
{
	return FString::Printf(TEXT(""));
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (const AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(Controller))
		{
			const float OneAttackDuration = bDurationProvideByController ? EnemyAIController->GetAttackDuration() : Duration;
			if (const UBlackboardComponent* BlackboardComponent = const_cast<UBlackboardComponent*>(EnemyAIController->
				GetBlackboardComponent()))
			{
				const float CoolDownTimer = BlackboardComponent->GetValueAsFloat(AttackCoolDownTimer.SelectedKeyName);
				if (CoolDownTimer > 0)
				{
					return CoolDownAttackResult;
				}
			}
			if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(EnemyAIController->GetPawn()))
			{
<<<<<<< HEAD
				if (UHoldComponent* HoldingComponent = GunplayCharacter->GetHoldingComponent())
=======
				if (UHoldingComponent* HoldingComponent = GunplayCharacter->GetHoldingComponent())
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
				{
					HoldingComponent->UseCurrentHolding();

					const FTimerDelegate FinishAttackDelegate = FTimerDelegate::CreateLambda(
						[&OwnerComp, HoldingComponent, this]
						{
							HoldingComponent->UsedCurrentHolding();
							FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
						});

					GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, FinishAttackDelegate, OneAttackDuration,
					                                       false);
					return EBTNodeResult::InProgress;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
