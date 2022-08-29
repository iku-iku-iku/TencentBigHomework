#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnlineGameMode.generated.h"

UCLASS(minimalapi)
class AOnlineGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Game")
	bool IsGameEnd() const { return bGameEnd; }
	
protected:
	void EndGame() const;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;
	
	int32 PlayerCount;
	
	UPROPERTY(BlueprintReadOnly, Category="Game")
	bool bGameEnd = false;
};
