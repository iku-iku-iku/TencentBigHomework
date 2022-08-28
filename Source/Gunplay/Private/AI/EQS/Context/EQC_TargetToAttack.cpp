// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/EQS/Context/EQC_TargetToAttack.h"

#include "AIController.h"
#include "AI/EQS/Test/EnvQueryTest_KeepDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEQC_TargetToAttack::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	if (const AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(QueryInstance.Owner))
	{
		if (const AAIController* Controller = Cast<AAIController>(EnemyCharacter->GetController()))
		{
			if (const UBlackboardComponent* BlackboardComponent = Controller->GetBlackboardComponent())
			{
				if (const AActor* TargetToAttack = Cast<AActor>(
					BlackboardComponent->GetValueAsObject(TEXT("TargetToAttack"))))
				{
					UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetToAttack);
					return;
				}
			}
		}
	}
	
	if (const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(
		UGameplayStatics::GetActorOfClass(this, APlayerCharacter::StaticClass())))
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerCharacter);
	}
}
