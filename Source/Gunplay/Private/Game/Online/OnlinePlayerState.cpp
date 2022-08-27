// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/OnlinePlayerState.h"

#include "Character/Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Game/GunplayGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"
#include "Util/GunplayUtils.h"

void AOnlinePlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (GIsClient)
	{
		UE_LOG(LogTemp, Warning, TEXT("设置玩家名称"))

		if (UGunplayGameInstance* GunplayGameInstance = UGunplayGameInstance::GetInstance())
		{
			Server_SetPlayerName(GunplayGameInstance->GetPlayerName().ToString());
		}
	}
}

void AOnlinePlayerState::OnRep_CharacterColor()
{
	GunplayUtils::UntilDo(GetWorld(), [this]
	{
		return Cast<APlayerCharacter>(GetPawn()) != nullptr;
	}, [this]
	{
		if (USkeletalMeshComponent* SkeletalMeshComponent = Cast<APlayerCharacter>(GetPawn())->GetMesh())
		{
			SkeletalMeshComponent->SetVectorParameterValueOnMaterials(
				TEXT("BodyColor"), CharacterColor);
		}
	});
}

void AOnlinePlayerState::Server_SetPlayerName_Implementation(const FString& Name)
{
	SetPlayerName(Name);
}

void AOnlinePlayerState::SetScore(const int32 NewValue)
{
	APlayerState::SetScore(NewValue > 0 ? NewValue : 0);
}

void AOnlinePlayerState::AddScore(const int32 Delta)
{
	SetScore(GetScore() + Delta);
}

void AOnlinePlayerState::SetRank(const int32 NewValue)
{
	if (Rank != NewValue)
	{
		// MARK_PROPERTY_DIRTY_FROM_NAME(AOnlinePlayerState, Rank, this);

		Rank = NewValue;
	}
}

void AOnlinePlayerState::OnRep_Rank()
{
}

void AOnlinePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// FDoRepLifetimeParams SharedParams;
	// SharedParams.bIsPushBased = true;
	//
	// DOREPLIFETIME_WITH_PARAMS_FAST(AOnlinePlayerState, Rank, SharedParams);
	DOREPLIFETIME(AOnlinePlayerState, Rank)
	DOREPLIFETIME(AOnlinePlayerState, CharacterColor)
}
