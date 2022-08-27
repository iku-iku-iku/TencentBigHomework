// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/EnemyAIController.h"

#include "Character/GunplayCharacter.h"

void AEnemyAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		if (AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(InPawn))
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller控制了一个敌人"))

			GunplayCharacter->OnDeath().AddUObject(this, &AEnemyAIController::OnAIDeath);
		}
	}
}

void AEnemyAIController::OnAIDeath(const AGunplayCharacter* GunplayCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("一个敌人被消灭了"))
	const_cast<AGunplayCharacter*>(GunplayCharacter)->Die();
}
