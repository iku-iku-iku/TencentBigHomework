// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "CreateSessionCallbackProxy.h"
#include "OnlineSessionSettings.h"
#include "Engine/GameInstance.h"
#include "GunplayGameInstance.generated.h"

DECLARE_EVENT_OneParam(UOnlineGameInstance, FOnlineGameInstanceOneParamEvent, bool)

UENUM()
enum class EGunplayMode : uint8 { Solitary, LanOnline, DSOnline };

/**
 * 全局游戏实例
 */
UCLASS()
class GUNPLAY_API UGunplayGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UGunplayGameInstance();

	virtual void Init() override;
public:
	static UGunplayGameInstance* GetInstance();

	FORCEINLINE FVector GetPlayerCharacterColor(const FUniqueNetIdRepl& UniqueId) const
	{
		if (const FVector* Vector = PlayerCharacterColorMap.Find(UniqueId))
		{
			return *Vector;
		}
		return {};
	}

	FORCEINLINE void SetPlayerCharacterColor(const FUniqueNetIdRepl& UniqueId, const FVector& Color)
	{
		PlayerCharacterColorMap.Add(UniqueId, Color);
	}

	const FText& GetPlayerName();

	FORCEINLINE void SetPlayerName(const FText& NewValue) { PlayerName = NewValue; }

	FORCEINLINE FOnlineGameInstanceOneParamEvent& OnFindSessionComplete() { return FindSessionCompleteEvent; }

	FORCEINLINE FOnlineGameInstanceOneParamEvent& OnCreateSessionComplete() { return CreateSessionCompleteEvent; }

	FORCEINLINE FOnlineGameInstanceOneParamEvent& OnDestroySessionComplete() { return DestroySessionCompleteEvent; }

	FORCEINLINE TArray<FOnlineSessionSearchResult>& GetSearchResults() const { return SessionSearch->SearchResults; }

	FORCEINLINE void SetGunplayMode(const EGunplayMode NewValue) { GunplayMode = NewValue; }

	FORCEINLINE static bool IsSolitary() { return GetInstance()->GunplayMode == EGunplayMode::Solitary; }
	FORCEINLINE static bool IsDSOnline() { return GetInstance()->GunplayMode == EGunplayMode::DSOnline; }
	FORCEINLINE static bool IsLanOnline() { return GetInstance()->GunplayMode == EGunplayMode::LanOnline; }

	FORCEINLINE bool IsDSInstance() const
	{
		return bIsDSInstance;;
	}

	FORCEINLINE bool HasEnteredRoom() const { return bHasEnteredRoom; }

	FORCEINLINE TSet<FUniqueNetIdRepl>& GetMatchPlayerUniqueNetIds() { return DS_MatchPlayerUniqueNetIds; }

	UFUNCTION(BlueprintCallable, Category="UI")
	void ShowMessage(FText Message);

	UFUNCTION(BlueprintCallable, Category="UI")
	class ULoadingWidget* ShowLoading(const FString& Message);

	UFUNCTION(BlueprintCallable, Category="UI")
	class UDialogWidget* ShowDialog();

	void CreateSession(int32 ConnNum);

	void SearchSession();

	virtual bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult) override;

	void DestroySession();

	void ResetDSLevel();

	static void AddSingleton(UClass* Class, UObject* Object);

	void AddSingletonInternal(UClass* Class, UObject* Object);

	FORCEINLINE static void AddSingleton(UObject* Singleton);

	template <typename ObjType>
	FORCEINLINE static ObjType* GetSingleton();

	UFUNCTION(BlueprintPure, Category="Game")
	UObject* GetSingleton(const UClass* Class) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Online")
	FText PlayerName{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Online")
	int32 MaxPlayerNum;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UMessageWidget> MessageWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class ULoadingWidget> LoadingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UDialogWidget> DialogWidgetClass;
	//
	// UPROPERTY(EditDefaultsOnly, Category="Online")
	// class ULoadingWidget* LoadingWidget;

	UPROPERTY(EditDefaultsOnly, Category="Online")
	FName DSLevelName = TEXT("Room");

	UPROPERTY(EditDefaultsOnly, Category="Gunplay")
	TSubclassOf<class UBleedingTextManager> BleedingTextManagerClass;

private:
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, enum EOnJoinSessionCompleteResult::Type Result);

	void OnFindSessionComplete(bool bWasSuccessful);

	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	FDelegateHandle OnFindSessionCompleteDelegateHandle;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;

	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	TSharedPtr<const FUniqueNetId> UserId;

	FOnlineGameInstanceOneParamEvent FindSessionCompleteEvent;

	FOnlineGameInstanceOneParamEvent CreateSessionCompleteEvent;

	FOnlineGameInstanceOneParamEvent DestroySessionCompleteEvent;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	FName CurrentSessionName;

	bool bIsLAN = false;

	EGunplayMode GunplayMode;

	uint8 bIsDSInstance : 1;
	uint8 bHasEnteredRoom : 1;

	TSet<FUniqueNetIdRepl> DS_MatchPlayerUniqueNetIds;

	UPROPERTY()
	TMap<UClass*, UObject*> SingletonMap;

	UPROPERTY()
	TMap<FUniqueNetIdRepl, FVector> PlayerCharacterColorMap;
};

void UGunplayGameInstance::AddSingleton(UObject* Singleton)
{
	AddSingleton(Singleton->GetClass(), Singleton);
}

template <typename ObjType>
ObjType* UGunplayGameInstance::GetSingleton()
{
	return Cast<ObjType>(GetInstance()->GetSingleton(ObjType::StaticClass()));
}
