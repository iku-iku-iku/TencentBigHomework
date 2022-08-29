// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/PickupComponent.h"
#include "Character/GunplayCharacter.h"
#include "Component/HoldComponent.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interface/BeObtainedInterface.h"
#include "Util/GunplayUtils.h"

UPickupComponent::UPickupComponent()
{
	SetIsReplicatedByDefault(true);

	PrimaryComponentTick.bCanEverTick = false;

	PickupTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Pickup Trigger"));

	PickupTrigger->SetupAttachment(this);

	PickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::OnBeginOverlap);

	SetPickable(false);

	PickupTrigger->SetCollisionResponseToChannel(ECC_GUN, ECR_Ignore);
}

void UPickupComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPickupComponent, OwnerPlayer)
	DOREPLIFETIME(UPickupComponent, bSimulatePhysics)
}


void UPickupComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (AGunplayCharacter* Player = Cast<AGunplayCharacter>(OtherActor))
	{
		if (const IBeObtainedInterface* BeObtainedInterface = Cast<IBeObtainedInterface>(GetOwner()))
		{
			BeObtainedInterface->Execute_BeObtainedBy(GetOwner(), Player);
		}
	}
}

void UPickupComponent::OnRep_bSimulatePhysics() const
{
	if (const AActor* Owner = GetOwner())
	{
		if (UMeshComponent* Mesh = GunplayUtils::GetComponent<UMeshComponent>(Owner))
		{
			if (bSimulatePhysics)
			{
				Mesh->SetSimulatePhysics(true);
				Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			}
			else
			{
				Mesh->SetSimulatePhysics(false);
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}
		}
	}
}

void UPickupComponent::DetachFromPlayer()
{
	OwnerPlayer->GetHoldingComponent()->RemoveHolding(GetOwner());
	GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void UPickupComponent::AttachToPlayer(AGunplayCharacter* Player)
{
	SetPickable(false);
	SetSimulatePhysics(false);
	OwnerPlayer = Player;
	GetOwner()->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
	                              SocketName);
	Player->GetHoldingComponent()->AddHolding(GetOwner());
}

void UPickupComponent::SetPickable(const bool bPickable) const
{
	PickupTrigger->SetGenerateOverlapEvents(bPickable);
}


void UPickupComponent::SetSimulatePhysics(const bool bNewSimulatePhysics)
{
	if (GetOwner()->HasAuthority())
	{
		bSimulatePhysics = bNewSimulatePhysics;
		OnRep_bSimulatePhysics();
	}
}
