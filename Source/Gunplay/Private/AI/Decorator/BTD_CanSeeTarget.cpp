// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Decorator/BTD_CanSeeTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"

UBTD_CanSeeTarget::UBTD_CanSeeTarget()
{
	NodeName = TEXT("能够看到目标");
}

bool UBTD_CanSeeTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (const AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (const APawn* Pawn = Controller->GetPawn())
		{
			if (const UBlackboardComponent* BlackboardComponent = Controller->GetBlackboardComponent())
			{
				if (const AActor* Target = Cast<AActor>(
					BlackboardComponent->GetValueAsObject(GetSelectedBlackboardKey())))
				{
					FVector Start = Pawn->GetActorLocation();
					FVector End = Target->GetActorLocation();
					const FVector Dir = (End - Start).GetSafeNormal();
					Start += Dir * 50.f;
					End += Dir * 100.f;

					FCollisionQueryParams TraceParams;
					TraceParams.AddIgnoredActor(Pawn);
					TraceParams.AddIgnoredActor(Target);
					return !(GetWorld()->LineTraceTestByChannel(Start, End, TraceChannel, TraceParams));
				}
			}
		}
	}

	return false;
}

void UBTD_CanSeeTarget::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UBTD_CanSeeTarget::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
