// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Decorator/BTD_Angle.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTD_Angle::UBTD_Angle()
{
	NodeName = TEXT("夹角");

	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTD_Angle, BlackboardKey), AActor::StaticClass());
}

void UBTD_Angle::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTD_Angle::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

bool UBTD_Angle::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
	{
		if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
		{
			if (const AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(GetSelectedBlackboardKey())))
			{
				const FVector TargetLocation = Target->GetActorLocation();
				const FVector TargetForward = Target->GetActorForwardVector();
				

				if (const AAIController* Controller = OwnerComp.GetAIOwner())
				{
					if (const APawn* SelfPawn = Controller->GetPawn())
					{
						const FVector SelfLocation = SelfPawn->GetActorLocation();
						const FVector TargetToSelfDir = (SelfLocation- TargetLocation).GetSafeNormal();

						const float AngleCos = FVector::DotProduct(TargetForward, TargetToSelfDir);
						const float DegreeCos = FMath::Cos(Degree);
						const float Delta = AngleCos - DegreeCos;

						return FMath::Sign(-Delta) == CompareType;
					}
				}
			}
		}
	}
	
	return false;
}
