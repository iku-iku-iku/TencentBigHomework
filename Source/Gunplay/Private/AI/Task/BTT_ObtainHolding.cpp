// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Task/BTT_ObtainHolding.h"

#include "AIController.h"
#include "Character/GunplayCharacter.h"

UBTT_ObtainHolding::UBTT_ObtainHolding()
{
	NodeName = TEXT("获得");
}

EBTNodeResult::Type UBTT_ObtainHolding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;

	if (const AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(Controller->GetPawn()))
		{
			GunplayCharacter->ObtainHolding(HoldingClass);
			NodeResult = EBTNodeResult::Succeeded;
		}
	}

	return NodeResult;
}

void UBTT_ObtainHolding::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
