// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Service/BTS_CheckHPLow.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Component/CharacterStatusComponent.h"
#include "Character/GunplayCharacter.h"

UBTS_CheckHPLow::UBTS_CheckHPLow()
{
	NodeName = TEXT("检查HP是否过低");
}

void UBTS_CheckHPLow::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Blackboard && ControlledCharacter)
	{
		const float HPRatio = ControlledCharacter->GetStatus()->GetHPRatio();
		Blackboard->SetValueAsBool(BlackboardKey.SelectedKeyName, HPRatio < Threshold);
	}
}
