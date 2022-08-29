// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GunplayCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Online/OnlinePlayerState.h"
#include "GunplayPlayerController.generated.h"

UCLASS()
class GUNPLAY_API AGunplayPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGunplayPlayerController();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category="Controller")
	class APlayerCharacter* GetPlayerCharacter() const { return ControlledPlayerCharacter; }

	FORCEINLINE void SetTurnSensitivity(const float NewValue) { TurnSensitivity = NewValue; }
	FORCEINLINE void SetLookUpSensitivity(const float NewValue) { LookUpSensitivity = NewValue; }
	FORCEINLINE float GetTurnSensitivity() const { return TurnSensitivity; }
	FORCEINLINE float GetLookUpSensitivity() const { return LookUpSensitivity; }

protected:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	virtual void OnPlayerDeath(const class APlayerCharacter* GunplayCharacter);

	UFUNCTION(BlueprintPure, Category="Controller")
	AOnlinePlayerState* GetState() const;

	UPROPERTY(EditDefaultsOnly, Category="Controller")
	TSubclassOf<class APlayerCharacter> SpawnCharacterClass;

	UPROPERTY()
	class APlayerCharacter* ControlledPlayerCharacter;

	bool bDead;
private:
	float TurnSensitivity = 0.f;
	float LookUpSensitivity = 0.f;

};
