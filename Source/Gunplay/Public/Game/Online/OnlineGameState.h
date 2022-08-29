// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include <map>

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "OnlineGameState.generated.h"

DECLARE_EVENT(AOnlineGunplayGameState, FRankReorderEvent)

UCLASS()
class GUNPLAY_API AOnlineGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	AOnlineGameState();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void AddPlayerState(APlayerState* PlayerState) override;

public:
	void ReorderPlayerStates();

	UFUNCTION(BlueprintPure, Category="Rank")
	int32 GetPlayerRank(const class APlayerState* PlayerState) const;

	UFUNCTION(BlueprintPure, Category="Rank")
	class APlayerState* GetAheadPlayer(const class APlayerState* PlayerState) const;

	UFUNCTION(BlueprintPure, Category="Rank")
	class APlayerState* GetBehindPlayer(const class APlayerState* PlayerState) const;

	FORCEINLINE TArray<class APlayerState*> const& GetPlayerStates() const { return PlayerArray; }

	FORCEINLINE FRankReorderEvent& OnRankReorder() { return RankReorderEvent; }

protected:
	FRankReorderEvent RankReorderEvent;

	TFunction<bool(class APlayerState*, class APlayerState*)> StatePtrComparator;

	TFunction<bool(class APlayerState&, class APlayerState&)> StateRefComparator;
};
