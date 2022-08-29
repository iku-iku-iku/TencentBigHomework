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

void AOnlinePlayerState::SetRank(const int32 NewValue)
{
	if (Rank != NewValue)
	{
		Rank = NewValue;
	}
}

void AOnlinePlayerState::OnRep_Rank()
{
}

void AOnlinePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOnlinePlayerState, Rank)
	DOREPLIFETIME(AOnlinePlayerState, CharacterColor)
}
