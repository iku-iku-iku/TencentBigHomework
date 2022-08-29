// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Game/Online/PlayerInfo.h"
#include "UI/SingletonWidget.h"
#include "RoomWidget.generated.h"

class URoomPlayerListItemWidget;
/**
 * 
 */
UCLASS()
class GUNPLAY_API URoomWidget : public USingletonWidget
{
	GENERATED_BODY()

public:
	void UpdatePlayerList(const TArray<FPlayerInfo>& PlayerInfos);

	void SetMapItemIndex(const int32 Index);
protected:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* PlayerList;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* MapNameText;

	UPROPERTY(meta=(BindWidget))
	class UButton* LeftSwitchMapBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* RightSwitchMapBtn;

	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* StartOrPrepare;

	UPROPERTY(meta=(BindWidget))
	class UButton* StartGameBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* PrepareBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* ResetColorBtn;

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void Prepare();

	UFUNCTION()
	void StartGame();
	
	UFUNCTION()
	void ResetCharacterColor();

	UFUNCTION(BlueprintCallable)
	void SwitchMapLeft();

	UFUNCTION(BlueprintCallable)
	void SwitchMapRight();

	UPROPERTY(EditDefaultsOnly, Category="Room")
	TSubclassOf<URoomPlayerListItemWidget> PlayerListItemWidgetClass;

	// 地图数据。在蓝图中设定
	UPROPERTY(EditDefaultsOnly, Category="Room")
	class UDataTable* MapTable;

private:

	TArray<FName> MapTableRowNames;

	void SetUIVisibility() const;
};
