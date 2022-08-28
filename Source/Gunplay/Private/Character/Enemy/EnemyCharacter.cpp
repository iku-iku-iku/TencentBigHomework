// Copyright iku-iku-iku,. All Rights Reserved.


#include "Character/Enemy/EnemyCharacter.h"

#include "AI/EnemyAIController.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager/BleedingTextManager.h"


AEnemyCharacter::AEnemyCharacter()
{
	bUseControllerRotationYaw = true;

	AIControllerClass = AEnemyAIController::StaticClass();

	AttackForwardArrowComponent = CreateDefaultSubobject<UArrowComponent>("Attack Forward");
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultController();

	bUseControllerRotationYaw = true;

	if (AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(Controller))
	{
		if (BehaviorTree)
		{
			EnemyAIController->RunBehaviorTree(BehaviorTree);
		}
	}

	for (UActorComponent* Component : GetComponents())
	{
		if (UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Component))
		{
			// Ignore敌人的射击通道，防止敌人射击到敌人
			PrimitiveComponent->SetCollisionResponseToChannel(ECC_Enemy_Shoot, ECR_Ignore);
		}
	}
}

void AEnemyCharacter::LookAt(const FVector& TargetLocation)
{
	const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

	FaceRotation(LookAtRotation);

	AttackForwardArrowComponent->SetWorldRotation(LookAtRotation);
}

FVector AEnemyCharacter::GetAttackForward() const
{
	return AttackForwardArrowComponent->GetForwardVector();
}
