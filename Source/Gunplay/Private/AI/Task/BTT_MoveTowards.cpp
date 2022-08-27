// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Task/BTT_MoveTowards.h"

#include "AIController.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTT_MoveTowards::UBTT_MoveTowards()
{
	NodeName = TEXT("移向");
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_MoveTowards, BlackboardKey));
}

EBTNodeResult::Type UBTT_MoveTowards::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::Failed;
	if (AAIController* Controller = OwnerComp.GetAIOwner())
	{
		if (const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent())
		{
			if (const ACharacter* Character = Cast<ACharacter>(Controller->GetPawn()))
			{
				if (UCharacterMovementComponent* CharacterMovementComponent = Character->GetCharacterMovement())
				{
					CharacterMovementComponent->MaxWalkSpeed = Speed;
				}
			}
			const FVector Target = BlackboardComponent->GetValueAsVector(GetSelectedBlackboardKey());
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Target);
			NodeResult = EBTNodeResult::Succeeded;
		}
	}
	return NodeResult;
}

void UBTT_MoveTowards::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

FString UBTT_MoveTowards::GetStaticDescription() const
{
	return FString::Printf(TEXT("目标：%s；速度：%f"), *GetSelectedBlackboardKey().ToString(), Speed);
}
