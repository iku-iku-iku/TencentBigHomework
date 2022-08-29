// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoListWidget.generated.h"

/**
 * 玩家在对局中可以查看其它玩家的当前信息
 * 如：分数、剩余命数
 */
UCLASS()
class GUNPLAY_API UPlayerInfoListWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
public:
	void UpdateRankItems();

protected:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* PlayerInfoList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPlayerInfoListItemWidget> ListItemClass;
};
