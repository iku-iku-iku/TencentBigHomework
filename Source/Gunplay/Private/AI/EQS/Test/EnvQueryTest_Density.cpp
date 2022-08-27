// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/EQS/Test/EnvQueryTest_Density.h"
#include "Engine/World.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"


UEnvQueryTest_Density::UEnvQueryTest_Density(const FObjectInitializer& ObjectInitializer)
{
	TestPurpose = EEnvTestPurpose::Score;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
	Cost = EEnvTestCost::Medium;
}

void UEnvQueryTest_Density::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}

	FloatValueMin.BindData(QueryOwner, QueryInstance.QueryID);
	const float MinThresholdValue = FloatValueMin.GetValue();

	FloatValueMax.BindData(QueryOwner, QueryInstance.QueryID);
	const float MaxThresholdValue = FloatValueMax.GetValue();

	TArray<AActor*> IgnoreActors;
	if (!QueryInstance.PrepareContext(Ignore, IgnoreActors))
	{
		return;
	}

	if (AActor* Querier = Cast<AActor>(QueryOwner))
	{
		IgnoreActors.Add(Querier);
	}

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
		TArray<FHitResult> OutHits;
		const FVector Start = ItemLocation, End = Start;
		FCollisionShape Sphere = FCollisionShape::MakeSphere(DetectRadius);
		GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, ECC_Pawn, Sphere);
		OutHits.RemoveAll([&IgnoreActors](const FHitResult& HitResult)
		{
			return IgnoreActors.Contains(HitResult.GetActor());
		});
		const float Score = OutHits.Num();
		It.SetScore(TestPurpose, FilterType, Score, MinThresholdValue, MaxThresholdValue);
	}
}

FText UEnvQueryTest_Density::GetDescriptionTitle() const
{
	return FText::FromString(FString::Printf(TEXT("%s"), *Super::GetDescriptionTitle().ToString()));
}

FText UEnvQueryTest_Density::GetDescriptionDetails() const
{
	return FText::FromString(
		FString::Printf(TEXT("检测半径：%.0f; 忽略：%s"),
		                DetectRadius,
		                *UEnvQueryTypes::DescribeContext(Ignore).ToString())
	);
}
