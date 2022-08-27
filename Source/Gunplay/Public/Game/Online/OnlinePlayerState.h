// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OnlinePlayerState.generated.h"


UCLASS()
class GUNPLAY_API AOnlinePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable)
	void Server_SetPlayerName(const FString& Name);

	UFUNCTION(BlueprintCallable, Category="State")
	void SetScore(const int32 NewValue);

	UFUNCTION(BlueprintCallable, Category="State")
	void AddScore(const int32 Delta);

	FORCEINLINE int32 GetPlayerScore() const
	{
		return static_cast<int32>(APlayerState::GetScore());
	}

	FORCEINLINE int32 GetRank() const { return Rank; }

	FORCEINLINE void SetColor(const FVector& Color) { CharacterColor = Color; }

	FORCEINLINE const FVector& GetColor() const { return CharacterColor; }

	void SetRank(const int32 NewValue);

	UFUNCTION()
	void OnRep_CharacterColor();

	UFUNCTION()
	virtual void OnRep_Rank();
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing=OnRep_Rank, BlueprintReadOnly, Category=PlayerState)
	int32 Rank;

	UPROPERTY(ReplicatedUsing=OnRep_CharacterColor)
	FVector CharacterColor;
};
