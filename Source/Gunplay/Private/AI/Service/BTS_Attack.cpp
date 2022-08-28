// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Service/BTS_Attack.h"

#include "AI/EnemyAIController.h"
#include "Character/GunplayCharacter.h"
#include "Component/HoldComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTS_Attack::UBTS_Attack()
{
	NodeName = TEXT("攻击");
}

void UBTS_Attack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Attack();

	SetInterval();
}

void UBTS_Attack::Attack()
{
	if (ControlledCharacter)
	{
		if (UHoldComponent* HoldingComponent = ControlledCharacter->GetHoldingComponent())
		{
			HoldingComponent->UseCurrentHolding();
			const FLatentActionInfo LatentActionInfo(0, FMath::Rand(), TEXT("FinishAttack"), this);
			UKismetSystemLibrary::Delay(this, OneAttackDuration, LatentActionInfo);
		}
	}
}

void UBTS_Attack::SetInterval()
{
	if (const AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(Controller))
	{
		Interval = EnemyAIController->GetAttackInterval();
		OneAttackDuration = EnemyAIController->GetAttackDuration();
	}
}

void UBTS_Attack::FinishAttack() const
{
	if (ControlledCharacter)
	{
		if (UHoldComponent* HoldingComponent = ControlledCharacter->GetHoldingComponent())
		{
			HoldingComponent->UsedCurrentHolding();
		}
	}
}
