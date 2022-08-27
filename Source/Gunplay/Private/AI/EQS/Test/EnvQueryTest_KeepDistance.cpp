// Copyright iku-iku-iku,. All Rights Reserved.


#include "AI/EQS/Test/EnvQueryTest_KeepDistance.h"

#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"


UEnvQueryTest_KeepDistance::UEnvQueryTest_KeepDistance(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer)
{
	SetWorkOnFloatValues(false);
	DistanceTo = UEnvQueryContext_Querier::StaticClass();
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
	ScoringEquation = EEnvTestScoreEquation::InverseLinear;
	TestPurpose = EEnvTestPurpose::FilterAndScore;
}

void UEnvQueryTest_KeepDistance::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
	{
		return;
	}


	const bool bWants = BoolValue.GetValue();

	// don't support context Item here, it doesn't make any sense
	TArray<FVector> ContextLocations;
	if (!QueryInstance.PrepareContext(DistanceTo, ContextLocations))
	{
		return;
	}


	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
		for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++)
		{
			const float Distance = (ItemLocation - ContextLocations[ContextIndex]).Size();
			const bool bWithin = FMath::Abs(Distance - KeepingDistance) < Deviation;
			It.SetScore(TestPurpose, FilterType, bWithin, bWants);
		}
	}
}

FText UEnvQueryTest_KeepDistance::GetDescriptionTitle() const
{
	return FText::FromString(FString::Printf(TEXT("%s: to %s"),
	                                         *Super::GetDescriptionTitle().ToString(),
	                                         *UEnvQueryTypes::DescribeContext(DistanceTo).ToString()));
}

FText UEnvQueryTest_KeepDistance::GetDescriptionDetails() const
{
	return FText::FromString(FString::Printf(TEXT("保持距离：%.0f"), KeepingDistance));
}
