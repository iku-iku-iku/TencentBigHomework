// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Decorator/BTD_WithinRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTD_WithinRange::UBTD_WithinRange()
{
	NodeName = TEXT("在范围内");
}

bool UBTD_WithinRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
	{
		float Value = 1e9f;
		const UStruct* KeyType = BlackboardKey.SelectedKeyType;
		if (KeyType->IsChildOf(UBlackboardKeyType_Vector::StaticClass()))
		{
			Value = BlackboardComponent->GetValueAsFloat(GetSelectedBlackboardKey());
		}
		if (KeyType->IsChildOf(UBlackboardKeyType_Object::StaticClass()))
		{
			if (const AActor* Actor = Cast<AActor>(BlackboardComponent->GetValueAsObject(GetSelectedBlackboardKey())))
			{
				if (const AAIController* Controller = OwnerComp.GetAIOwner())
				{
					if (const APawn* Pawn = Controller->GetPawn())
					{
						Value = FVector::Distance(Actor->GetActorLocation(), Pawn->GetActorLocation());
					}
				}
			}
		}

		return Min < Value && Value < Max;
	}
	return false;
}

void UBTD_WithinRange::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UBTD_WithinRange::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
