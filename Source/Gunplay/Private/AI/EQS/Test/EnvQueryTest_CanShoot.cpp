// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/EQS/Test/EnvQueryTest_CanShoot.h"

#include "DrawDebugHelpers.h"
#include "Character/GunplayCharacter.h"
#include "Component/HoldComponent.h"
#include "Component/ShootComponent.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
#include "Util/GunplayUtils.h"

UEnvQueryTest_CanShoot::UEnvQueryTest_CanShoot(const FObjectInitializer& ObjectInitializer)
{
	SetWorkOnFloatValues(false);
	Cost = EEnvTestCost::High;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
	TestPurpose = EEnvTestPurpose::Filter;
}

void UEnvQueryTest_CanShoot::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}

	if (const AGunplayCharacter* Querier = Cast<AGunplayCharacter>(QueryOwner))
	{
		if (const UHoldComponent* HoldingComponent = Querier->GetHoldingComponent())
		{
			if (const UShootComponent* ShootComponent =
				GunplayUtils::GetComponent_Const<UShootComponent>(HoldingComponent->GetCurrentHolding()))
			{
				const bool bWants = BoolValue.GetValue();

				TArray<AActor*> TargetActors;
				if (!QueryInstance.PrepareContext(Target, TargetActors))
				{
					return;
				}

				for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
				{
					const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
					for (const AActor* TargetActor : TargetActors)
					{
						bool bCanShoot = false;

						FHitResult HitResult;

						FVector Start = ItemLocation;
						FVector End = TargetActor->GetActorLocation();

						End += (End - Start).GetSafeNormal() * 100.f;

						if (ShootComponent->ShootDetect(Start, End, HitResult, ECC_Enemy_Shoot, Querier))
						{
							if (const AActor* HitActor = HitResult.GetActor())
							{
								bCanShoot = HitActor == TargetActor;
							}
						}

						It.SetScore(TestPurpose, FilterType, bCanShoot, bWants);
					}
				}
			}
		}
	}
}

FText UEnvQueryTest_CanShoot::GetDescriptionTitle() const
{
	return Super::GetDescriptionTitle();
}

FText UEnvQueryTest_CanShoot::GetDescriptionDetails() const
{
	return Super::GetDescriptionDetails();
}
