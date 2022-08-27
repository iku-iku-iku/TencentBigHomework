// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Task/BTT_UpdateCoolDown.h"

#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_UpdateCoolDown::UBTT_UpdateCoolDown()
{
	NodeName = TEXT("更新冷却");

	BlackboardKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_UpdateCoolDown, BlackboardKey));
}

EBTNodeResult::Type UBTT_UpdateCoolDown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;
	if (bUseAttackIntervalAsCoolDown)
	{
		if (AAIController* Controller = OwnerComp.GetAIOwner())
		{
			if (const AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(Controller))
			{
				const float Interval = EnemyAIController->GetAttackInterval();

				if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
				{
					BlackboardComponent->SetValueAsFloat(GetSelectedBlackboardKey(), Interval);

					NodeResult = EBTNodeResult::Succeeded;
				}
			}
		}
	}
	else
	{
		if (UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsFloat(GetSelectedBlackboardKey(), CoolDownTime);
			
			NodeResult = EBTNodeResult::Succeeded;
		}
	}

	return NodeResult;
}

void UBTT_UpdateCoolDown::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
