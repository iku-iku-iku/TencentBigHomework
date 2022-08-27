// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Task/BTT_Jump.h"

#include "AIController.h"
#include "Character/GunplayCharacter.h"

UBTT_Jump::UBTT_Jump()
{
	NodeName = TEXT("跳起");
}

EBTNodeResult::Type UBTT_Jump::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;
	if (const AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(Controller->GetPawn()))
		{
			GunplayCharacter->Jump();
			NodeResult = EBTNodeResult::Succeeded;
		}
	}
	return NodeResult;
}

void UBTT_Jump::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
