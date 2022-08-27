// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Task/BTT_LookAt.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/GunplayCharacter.h"
#include "Character/Enemy/EnemyCharacter.h"


UBTT_LookAt::UBTT_LookAt()
{
	NodeName = TEXT("看向");
}

EBTNodeResult::Type UBTT_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(AIController->GetPawn()))
		{
			if (const UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent())
			{
				if (const AActor* Target = Cast<AActor>(
					BlackboardComponent->GetValueAsObject(GetSelectedBlackboardKey())))
				{
					EnemyCharacter->LookAt(Target->GetActorLocation());

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}

void UBTT_LookAt::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

FString UBTT_LookAt::GetStaticDescription() const
{
	return FString::Printf(TEXT("目标：%s"), *BlackboardKey.SelectedKeyName.ToString());
}
