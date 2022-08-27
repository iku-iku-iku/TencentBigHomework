// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/HoldingComponent.h"
#include "Engine/World.h"
#include "Algo/Count.h"
#include "GameFramework/Actor.h"
#include "Interface/UseInterface.h"
#include "Net/UnrealNetwork.h"

UHoldingComponent::UHoldingComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = true;
}

void UHoldingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bUsingHolding)
	{
		UsingCurrentHolding(DeltaTime);
	}
}


void UHoldingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHoldingComponent, HoldingSlots)
	DOREPLIFETIME(UHoldingComponent, Rep_Holdings)
	DOREPLIFETIME(UHoldingComponent, CurrentHoldingIndex)
	DOREPLIFETIME(UHoldingComponent, OldHoldingIndex)
}


void UHoldingComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	for (AActor* Holding : Rep_Holdings)
	{
		if (Holding)
		{
			Holding->Destroy();
		}
	}
}

void UHoldingComponent::OnRep_Holdings()
{
	SwitchShowingHolding(OldHoldingIndex, CurrentHoldingIndex);
}

void UHoldingComponent::SwitchShowingHolding(int32 OldIndex, int32 NewIndex)
{
	if (HoldingSlots.IsValidIndex(OldIndex) && HoldingSlots[OldIndex])
	{
		HoldingSlots[OldIndex]->SetActorHiddenInGame(true);
	}
	if (HoldingSlots.IsValidIndex(NewIndex) && HoldingSlots[NewIndex])
	{
		HoldingSlots[NewIndex]->SetActorHiddenInGame(false);
	}

	SwitchHoldingEvent.Broadcast();
}

void UHoldingComponent::OnRep_CurrentHoldingIndex()
{
	SwitchShowingHolding(OldHoldingIndex, CurrentHoldingIndex);
}

void UHoldingComponent::SwitchHoldingWithAxis(float Value)
{
	if (Value > 0) { SwitchHoldingRight(); }
	else if (Value < 0) { SwitchHoldingLeft(); }
}

void UHoldingComponent::UseCurrentHolding()
{
	bUsingHolding = true;
	if (AActor* CurrentHolding = GetCurrentHolding())
	{
		if (IUseInterface* UseInterface = Cast<IUseInterface>(CurrentHolding))
		{
			UseInterface->Use();
		}
	}
}

void UHoldingComponent::UsingCurrentHolding(float DeltaTime)
{
	if (AActor* CurrentHolding = GetCurrentHolding())
	{
		if (IUseInterface* UseInterface = Cast<IUseInterface>(CurrentHolding))
		{
			UseInterface->Using(DeltaTime);
		}
	}
}

void UHoldingComponent::UsedCurrentHolding()
{
	bUsingHolding = false;
	if (AActor* CurrentHolding = GetCurrentHolding())
	{
		if (IUseInterface* UseInterface = Cast<IUseInterface>(CurrentHolding))
		{
			UseInterface->Used();
		}
	}
}

int32 UHoldingComponent::GetHoldingNum(const TSubclassOf<AActor> HoldingClass) const
{
	return Algo::CountIf(Rep_Holdings, [&HoldingClass](const AActor* X)
	{
		return X->GetClass()->IsChildOf(HoldingClass);
	});
}

void UHoldingComponent::AddHolding(AActor* Holding)
{
	Holding->SetActorHiddenInGame(true);
	Holding->SetOwner(GetOwner());
	UClass* HoldingClass = Holding->GetClass();

	// 如果没有该类型，则添加到Holdings中
	if (!Rep_Holdings.ContainsByPredicate([&HoldingClass](const AActor* X)
	{
		return IsValid(X) && X->GetClass() == HoldingClass;
	}))
	{
		HoldingSlots.Add(Holding);
	}

	Rep_Holdings.Add(Holding);

	// 切换到获得的物品上
	if (CurrentHoldingIndex < 0 || bSwitchToWhenPickup)
	{
		SetCurrentHoldingIndex(HoldingSlots.Num() - 1);
	}
}

void UHoldingComponent::RemoveHolding(AActor* Holding)
{
	UClass* HoldingClass = Holding->GetClass();
	Rep_Holdings.Remove(Holding);

	if (AActor** Next = Rep_Holdings.FindByPredicate([&HoldingClass](const AActor* X)
	{
		return X->GetClass() == HoldingClass;
	}))
	{
		// 如果还有同类叠加物品，则继续拿着同类物品
		HoldingSlots[HoldingSlots.IndexOfByKey(Holding)] = *Next;
	}
	else
	{
		// 没有同类物品，从slots中移除
		HoldingSlots.Remove(Holding);
	}
	if (CurrentHoldingIndex >= HoldingSlots.Num())
	{
		// 删除了最后一个slot
		SetCurrentHoldingIndex(CurrentHoldingIndex - 1);
	}
	else
	{
		// 移到下一个slot
		SetCurrentHoldingIndex(CurrentHoldingIndex);
	}
	OnRep_CurrentHoldingIndex();
	CurrentIndexId++;
}

AActor* UHoldingComponent::GetCurrentHolding() const
{
	if (CurrentHoldingIndex >= 0 && CurrentHoldingIndex < HoldingSlots.Num())
	{
		return HoldingSlots[CurrentHoldingIndex];
	}
	return nullptr;
}

void UHoldingComponent::SwitchHoldingRight()
{
	if (HoldingSlots.Num() > 0)
	{
		SetCurrentHoldingIndex((CurrentHoldingIndex + 1) % HoldingSlots.Num());
	}
}

void UHoldingComponent::SwitchHoldingLeft()
{
	if (HoldingSlots.Num() > 0)
	{
		SetCurrentHoldingIndex((CurrentHoldingIndex - 1 + HoldingSlots.Num()) % HoldingSlots.Num());
	}
}

void UHoldingComponent::SwitchHolding(const TSubclassOf<AActor> TargetClass)
{
	if (HoldingSlots.Num() > 0 && TargetClass)
	{
		for (int i = 0; i < HoldingSlots.Num(); i++)
		{
			if (HoldingSlots[i]->GetClass()->IsChildOf(TargetClass))
			{
				SetCurrentHoldingIndex(i);
				break;
			}
		}
	}
}

AActor* UHoldingComponent::FindHolding(UClass* HoldingClass)
{
	if (AActor** Res = Rep_Holdings.FindByPredicate([&HoldingClass](const AActor* X)
	{
		return IsValid(X) && X->GetClass() == HoldingClass;
	}))
	{
		return *Res;
	}
	return nullptr;
}


void UHoldingComponent::Server_SetCurrentHoldingIndex_Implementation(const int32 NewIndex)
{
	if (! HoldingSlots.IsValidIndex(NewIndex)) return;

	if (CurrentHoldingIndex != NewIndex)
	{
		OldHoldingIndex = CurrentHoldingIndex;
		CurrentHoldingIndex = NewIndex;
		OnRep_CurrentHoldingIndex();
	}
}
