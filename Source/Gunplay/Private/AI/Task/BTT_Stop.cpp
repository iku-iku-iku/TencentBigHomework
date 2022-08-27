// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Task/BTT_Stop.h"

#include "NavigationSystem.h"
#include "AIModule/Classes/AIController.h"
#include "Logging/MessageLog.h"
#include "Navigation/PathFollowingComponent.h"


namespace
{
	UPathFollowingComponent* InitNavigationControl(AAIController* AIController)
	{
		UPathFollowingComponent* PathFollowingComp = nullptr;

		if (AIController)
		{
			PathFollowingComp = AIController->GetPathFollowingComponent();
		}
		else
		{
			PathFollowingComp = AIController->FindComponentByClass<UPathFollowingComponent>();
			if (PathFollowingComp == nullptr)
			{
				PathFollowingComp = NewObject<UPathFollowingComponent>(AIController);
				PathFollowingComp->RegisterComponentWithWorld(AIController->GetWorld());
				PathFollowingComp->Initialize();
			}
		}

		return PathFollowingComp;
	}
}

UBTT_Stop::UBTT_Stop()
{
	NodeName = TEXT("停下");
}

EBTNodeResult::Type UBTT_Stop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;
	if (AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (Stop(Controller))
		{
			NodeResult = EBTNodeResult::Succeeded;
		}
	}
	return NodeResult;
}

void UBTT_Stop::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	UE_LOG(LogAI, Warning, TEXT("停下"))
}

bool UBTT_Stop::Stop(AAIController* Controller)
{
	UPathFollowingComponent* PFollowComp = InitNavigationControl(Controller);

	if (PFollowComp == nullptr || !PFollowComp->IsPathFollowingAllowed())
	{
		return false;
	}
	PFollowComp->SetStopMovementOnFinish(true);
	PFollowComp->OnPathFinished(FPathFollowingResult(EPathFollowingResult::Aborted,
	                                                 FPathFollowingResultFlags::UserAbortFlagMask));

	return true;
}
