// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MatchInfoWidget.generated.h"

/*
 * 展示对局信息
 */
UCLASS()
class GUNPLAY_API UMatchInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	class UVerticalBox* RankPreview;

	UPROPERTY(EditDefaultsOnly, Category="Match")
	TSubclassOf<class UPlayerInfoListItemWidget> PreviewPlayerInfoListItemClass;

	UPROPERTY(VisibleAnywhere, Category="Match")
	int32 RankPreviewCount = 3;

	void UpdateRankItems();
};
