// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Service/BTS_SetStatus.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/GunplayCharacter.h"
#include "Component/CharacterStatusComponent.h"

UBTS_SetStatus::UBTS_SetStatus()
{
	bCreateNodeInstance = true;
	NodeName= TEXT("设定状态");
	Interval = 0.2f;
	RandomDeviation = 0.f;
}

void UBTS_SetStatus::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (ControlledCharacter)
	{
		if (const UCharacterStatusComponent* CharacterStatusComponent = ControlledCharacter->GetStatus())
		{
			const float HPRatio = CharacterStatusComponent->GetHPRatio();

			if (Blackboard)
			{
				Blackboard->SetValueAsFloat(TEXT("HPRatio"), HPRatio);
			}
		}
	}
}
