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
#include "Game/Online/OnlineGunplayGameState.h"
#include "UI/Game/RankListWidget.h"
#include "Util/GunplayUtils.h"

void AOnlinePlayerController::Client_EndGame_Implementation()
{
	bIsGameEnd = true;
	if (UUserWidget* EndUI = CreateWidget(this, EndWidgetClass))
	{
		EndUI->AddToViewport();
	}
	ShowRankList();
}

void AOnlinePlayerController::Client_SetCountDownTimer_Implementation(const int32 NewValue)
{
	CountDownTimer = NewValue;
}

void AOnlinePlayerController::BeginPlay()
{
	Super::BeginPlay();

	GunplayUtils::GetAllActorsOfClassChecked(this, PlayerStarts);

	if (IsLocalPlayerController())
	{
		RankListWidget = CreateWidget<URankListWidget>(this, RankListWidgetClass);
		if (RankListWidget) { RankListWidget->AddToViewport(); }
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
				FVector Color = GunplayGameInstance->GetPlayerCharacterColor(UniqueNetId);
				// Color += GunplayUtils::FRandVector() * 1e-4;
				OnlinePlayerState->SetColor(Color);

				OnlinePlayerState->OnRep_CharacterColor();
			}
		}
	}
}

void AOnlinePlayerController::OnPlayerDeath(const APlayerCharacter* GunplayCharacter)
{
	Super::OnPlayerDeath(GunplayCharacter);

	if (APlayerCharacter* PlayerCharacter = const_cast<APlayerCharacter*>(GunplayCharacter))
	{
		PlayerCharacter->Die();
	}

	PlayerState->SetIsSpectator(true);
	ChangeState(NAME_Spectating);

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AOnlinePlayerController::RespawnPlayer,
	                                RespawnDelayTime, false);
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
			}
		}
	}
}

void AOnlinePlayerController::ShowRankList()
{
	if (RankListWidget)
	{
		RankListWidget->SetVisibility(ESlateVisibility::Visible);
		RankListWidget->UpdateRankItems();
	}
}

void AOnlinePlayerController::HideRankList()
{
	if (!bIsGameEnd && RankListWidget)
	{
		RankListWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
