// Copyright iku-iku-iku,. All Rights Reserved.

#include "AI/Task/BTT_Throw.h"
#include "Engine/World.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Enemy/EnemyCharacter.h"
<<<<<<< HEAD
#include "Component/HoldComponent.h"
=======
#include "Component/HoldingComponent.h"
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
#include "Interface/BeObtainedInterface.h"
#include "Interface/UseInterface.h"

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
					CreateThrowHolding(EnemyCharacter);

<<<<<<< HEAD
					if (UHoldComponent* HoldingComponent = EnemyCharacter->GetHoldingComponent())
=======
					if (UHoldingComponent* HoldingComponent = EnemyCharacter->GetHoldingComponent())
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
					{
						if (AActor* CurrentHolding = HoldingComponent->GetCurrentHolding())
						{
							if (CurrentHolding->GetClass() == ThrowHoldingClass)
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
	}
	return NodeResult;
}

void UBTT_Throw::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UBTT_Throw::CreateThrowHolding(AGunplayCharacter* Receiver) const
{
	Receiver->ObtainHolding(ThrowHoldingClass);
}

bool UBTT_Throw::ThrowAt(const AActor* Target, AActor* ThrowThing, AEnemyCharacter* EnemyCharacter)
{
	check(EnemyCharacter != nullptr && Target != nullptr && ThrowThing != nullptr)

	if (IUseInterface* UseInterface = Cast<IUseInterface>(ThrowThing))
	{
		const FVector TargetLocation = Target->GetActorLocation();
		const FVector CurrentLocation = EnemyCharacter->GetActorLocation();
		const float Distance = FVector::Distance(TargetLocation, CurrentLocation);
		FVector LookAtLocation = (TargetLocation + CurrentLocation) / 2;
		LookAtLocation.Z = Distance * LookHeightScale;

		EnemyCharacter->LookAt(LookAtLocation);

		EnemyCharacter->Jump();
		UseInterface->Use();
		UseInterface->Used();


		if (UMeshComponent* MeshComponent = Cast<UMeshComponent>(
			ThrowThing->GetComponentByClass(UMeshComponent::StaticClass())))
		{
			UE_LOG(LogAI, Warning, TEXT("Current Velocity %s"), *MeshComponent->GetPhysicsLinearVelocity().ToString());
		}
		return true;
	}
	return false;
}
