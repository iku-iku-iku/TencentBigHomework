// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/Service/BTS_SetHatred.h"

#include "AIController.h"
#include "Character/GunplayCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Player/PlayerCharacter.h"

UBTS_SetHatred::UBTS_SetHatred()
{
	NodeName = TEXT("设定仇恨对象");

	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_SetHatred, BlackboardKey), AActor::StaticClass());
}

void UBTS_SetHatred::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (APlayerCharacter* PlayerCharacter = FindHatred())
	{
		if (Blackboard)
		{
			Blackboard->SetValueAsObject(BlackboardKey.SelectedKeyName, PlayerCharacter);
		}
	}
}


APlayerCharacter* UBTS_SetHatred::FindHatred() const
{
	if (ControlledCharacter)
	{
		TArray<AActor*> PlayerCharacters;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), PlayerCharacters);
		float MinDist = MAX_FLT;
		AActor* Closest = nullptr;
		const FVector SelfLocation = ControlledCharacter->GetActorLocation();
		for (AActor* PlayerCharacter : PlayerCharacters)
		{
			const float Dist = FVector::DistSquared(PlayerCharacter->GetActorLocation(), SelfLocation);
			if (Dist < MinDist)
			{
				MinDist = Dist;
				Closest = PlayerCharacter;
			}
		}

		return Cast<APlayerCharacter>(Closest);
	}
	return nullptr;
}
