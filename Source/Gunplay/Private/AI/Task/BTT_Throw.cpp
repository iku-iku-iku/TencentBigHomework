// Copyright iku-iku-iku,. All Rights Reserved.

#include "AI/Task/BTT_Throw.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Component/HoldComponent.h"
#include "Component/ProjectileComponent.h"
#include "Interface/UseInterface.h"
#include "Util/GunplayUtils.h"

UBTT_Throw::UBTT_Throw()
{
	NodeName = TEXT("投掷");
}

EBTNodeResult::Type UBTT_Throw::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;

	if (const AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Controller->GetPawn()))
		{
			if (const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
			{
				if (const AActor* Target = Cast<AActor>(
					BlackboardComponent->GetValueAsObject(GetSelectedBlackboardKey())))
				{
					if (const UHoldComponent* HoldingComponent = EnemyCharacter->GetHoldingComponent())
					{
						if (AActor* CurrentHolding = HoldingComponent->GetCurrentHolding())
						{
							if (ThrowAt(Target, CurrentHolding, EnemyCharacter))
							{
								NodeResult = EBTNodeResult::Succeeded;
							}
						}
					}
				}
			}
		}
	}

	return NodeResult;
}

void UBTT_Throw::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

bool UBTT_Throw::ThrowAt(const AActor* Target, AActor* Projectile, AEnemyCharacter* AICharacter) const
{
	check(AICharacter != nullptr && Target != nullptr && Projectile != nullptr)

	if (IUseInterface* UseInterface = Cast<IUseInterface>(Projectile))
	{
		const FVector TargetLocation = Target->GetActorLocation();
		const FVector CurrentLocation = AICharacter->GetActorLocation();
		const float Distance = FVector::Distance(TargetLocation, CurrentLocation);

		AICharacter->LookAt(TargetLocation);

		if (UProjectileComponent* ProjectileComponent = GunplayUtils::GetComponent<UProjectileComponent>(Projectile))
		{
			// 距离越远，抛掷力度越大
			ProjectileComponent->SetProjectForce(Distance * ThrowForceScale);
		}

		AICharacter->Jump();
		UseInterface->Use();
		UseInterface->Used();

		return true;
	}
	return false;
}
