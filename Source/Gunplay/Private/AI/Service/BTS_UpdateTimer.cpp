// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Service/BTS_UpdateTimer.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTS_UpdateTimer::UBTS_UpdateTimer()
{
	NodeName = TEXT("更新计时器");

	bCreateNodeInstance = true;

	Interval = 0.2f;
	RandomDeviation = 0;
}

void UBTS_UpdateTimer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	for (FBlackboardKeySelector TimerSelector : Timers)
	{
		if (Blackboard)
		{
			const float OldTime = Blackboard->GetValueAsFloat(TimerSelector.SelectedKeyName);
			Blackboard->SetValueAsFloat(TimerSelector.SelectedKeyName, OldTime - DeltaSeconds);
		}
	}
}
