// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Service/GunplayBTSBase.h"

#include "AIController.h"
#include "Character/GunplayCharacter.h"

UGunplayBTSBase::UGunplayBTSBase()
{
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

void UGunplayBTSBase::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UGunplayBTSBase::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UGunplayBTSBase::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	Controller = Cast<AAIController>(OwnerComp.GetOwner());
	if (Controller)
	{
		ControlledCharacter = Cast<AGunplayCharacter>(Controller->GetPawn());

		Blackboard = Controller->GetBlackboardComponent();
	}
}
