// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Service/BTS_SetTargetDistance.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/GunplayCharacter.h"

UBTS_SetTargetDistance::UBTS_SetTargetDistance()
{
	NodeName = TEXT("设定目标距离");
}

void UBTS_SetTargetDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Blackboard && ControlledCharacter)
	{
		if (const AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject(TargetKey.SelectedKeyName)))
		{
			const float Dist = FVector::Distance(Target->GetActorLocation(), ControlledCharacter->GetActorLocation());

			Blackboard->SetValueAsFloat(BlackboardKey.SelectedKeyName, Dist);
		}
	}
}
