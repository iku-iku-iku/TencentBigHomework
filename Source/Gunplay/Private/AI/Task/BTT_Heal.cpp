// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Task/BTT_Heal.h"

#include "AIController.h"
#include "Character/GunplayCharacter.h"
#include "Component/CharacterStatusComponent.h"

UBTT_Heal::UBTT_Heal()
{
	NodeName = TEXT("回血");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTT_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;

	if (const AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (const UWorld* World = Controller->GetWorld())
		{
			const float CurrentTime = World->GetTimeSeconds();
			const float ElapseTime = CurrentTime - LastTime;
			LastTime = CurrentTime;
			Timer -= ElapseTime;
		}
		if (Timer < 0)
		{
			Timer = HealInterval;
			if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(Controller->GetPawn()))
			{
				if (UCharacterStatusComponent* CharacterStatusComponent = GunplayCharacter->GetStatus())
				{
					CharacterStatusComponent->AddHP(CharacterStatusComponent->GetMaxHP() * HealRatio);
					NodeResult = EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return NodeResult;
}

void UBTT_Heal::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}
