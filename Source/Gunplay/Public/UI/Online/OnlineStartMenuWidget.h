// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineStartMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API UOnlineStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
protected:
	UPROPERTY(meta=(BindWidget))
	class UButton* ExitBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* SettingBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* SearchRoomBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* CreateRoomBtn;

	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta=(BindWidget))
	class URoomListWidget* RoomList;

	UPROPERTY(EditDefaultsOnly, Category = "Online")
	TSubclassOf<class ULoadingWidget> LoadingWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Online")
	FName GunplayStartLevelName = TEXT("Start");

private:
	UFUNCTION()
	void Exit();

	UFUNCTION()
	void Setting();

	UFUNCTION()
	void CreateRoom();

	UFUNCTION()
	void SearchRoom();

	UFUNCTION()
	void OnFindSessionComplete(bool bWasSuccessful);

	UFUNCTION()
	void OnCreateSessionComplete(bool bWasSuccessful);

	bool CheckNameSet() const;

	UPROPERTY()
	class ULoadingWidget* LoadingWidget;
};
