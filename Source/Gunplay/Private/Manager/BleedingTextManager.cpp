// Copyright iku-iku-iku,. All Rights Reserved.


#include "Manager/BleedingTextManager.h"

#include "GameActor/BleedingText.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Game/GunplayGameInstance.h"
#include "Util/GunplayUtils.h"


void UBleedingTextManager::SpawnBleedingTextAt(const FVector& Location, const int32 BleedingNum)
{
	while (BleedingTextPool.Num() > 0 && ! IsValid(BleedingTextPool.Top()))
	{
		UE_LOG(LogTemp, Warning, TEXT("除去不可用的BleedingText"))

		BleedingTextPool.Pop(false);
	}

	if (BleedingTextPool.Num() == 0)
	{
		FillBleedingText();
	}

	if (BleedingTextPool.Num() != 0)
	{
		ABleedingText* BleedingText = BleedingTextPool.Pop(false);
		ensure(BleedingText);
		if (IsValid(BleedingText))
		{
			const FVector RandomOffset = GunplayUtils::RandOffset(RandomDeviation);
			BleedingText->ShowBleeding(Location + RandomOffset, BleedingNum);
		}
	}
}

void UBleedingTextManager::AddToPool(ABleedingText* BleedingText)
{
	check(IsValid(BleedingText))

	if (BleedingText)
	{
		BleedingTextPool.Add(BleedingText);
		BleedingText->SetHidden();
	}
}

UBleedingTextManager* UBleedingTextManager::GetInstance()
{
	return UGunplayGameInstance::GetSingleton<UBleedingTextManager>();
}

void UBleedingTextManager::FillBleedingText()
{
	if (BleedingTextClass)
	{
		if (UWorld* World = GetWorld())
		{
			ABleedingText* BleedingText = World->SpawnActor<ABleedingText>(BleedingTextClass);
			check(BleedingText)
			{
				AddToPool(BleedingText);
			}
		}
	}
}
