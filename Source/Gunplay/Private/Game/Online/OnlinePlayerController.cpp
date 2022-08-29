// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Online/OnlinePlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Character/GunplayCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Game/GunplayGameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Online/OnlineGameState.h"
#include "UI/Game/PlayerInfoListWidget.h"
#include "Util/GunplayUtils.h"

void AOnlinePlayerController::Client_EndGame_Implementation()
{
	bIsGameEnd = true;
	if (UUserWidget* EndUI = CreateWidget(this, EndWidgetClass))
	{
		EndUI->AddToViewport();
	}
	ShowPlayerInfoList();
}

void AOnlinePlayerController::BeginPlay()
{
	Super::BeginPlay();

	GunplayUtils::GetAllActorsOfClassChecked(this, PlayerStarts);

	if (IsLocalPlayerController())
	{
		PlayerInfoListWidget = CreateWidget<UPlayerInfoListWidget>(this, PlayerInfoListWidgetClass);
		if (PlayerInfoListWidget) { PlayerInfoListWidget->AddToViewport(); }
	}
}

void AOnlinePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AOnlinePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (HasAuthority() && InPawn)
	{
		if (const UGunplayGameInstance* GunplayGameInstance = UGunplayGameInstance::GetInstance())
		{
			if (AOnlinePlayerState* OnlinePlayerState = GetState())
			{
				const FUniqueNetIdRepl UniqueNetId = GetPlayerState<APlayerState>()->GetUniqueId();
				const FVector Color = GunplayGameInstance->GetPlayerCharacterColor(UniqueNetId);
				
				OnlinePlayerState->SetColor(Color);

				OnlinePlayerState->OnRep_CharacterColor();
			}
		}
	}
}

void AOnlinePlayerController::RespawnPlayer()
{
	if (const int PlayerStartsNum = PlayerStarts.Num() > 0)
	{
		if (const APlayerStart* RandomStart = GunplayUtils::RandChoice(PlayerStarts))
		{
			const FVector Location = RandomStart->GetActorLocation() + GunplayUtils::RandGroundOffset(
				RespawnStartOffset);
			if (APlayerCharacter* NewPlayer = GetWorld()->SpawnActor<APlayerCharacter>(
				SpawnCharacterClass, Location, GunplayUtils::RandYawRotator()))
			{
				Possess(NewPlayer);

				PlayerState->SetIsSpectator(false);
				ChangeState(NAME_Playing);

				bDead = false;
			}
		}
	}
}

void AOnlinePlayerController::ShowPlayerInfoList()
{
	if (PlayerInfoListWidget)
	{
		PlayerInfoListWidget->SetVisibility(ESlateVisibility::Visible);
		PlayerInfoListWidget->UpdateRankItems();
	}
}

void AOnlinePlayerController::HidePlayerInfoList()
{
	if (!bIsGameEnd && PlayerInfoListWidget)
	{
		PlayerInfoListWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
