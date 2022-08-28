// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Item/RankListItemWidget.h"
#include "RankListWidget.generated.h"

/**
 * 
 */
UCLASS()
class GUNPLAY_API URankListWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
public:
	void UpdateRankItems();

protected:
	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* RankList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URankListItemWidget> RankListItemClass;
};
