// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game/GunplayGameInstance.h"
#include "GunplayStartWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class GUNPLAY_API UGunplayStartWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* SolitaryBtn;

	UPROPERTY(meta=(BindWidget))
	UButton* LANBtn;

	UPROPERTY(meta=(BindWidget))
	UButton* DSBtn;

	UPROPERTY(EditDefaultsOnly, Category="Gunplay")
	FName SolitaryLevel;

	UPROPERTY(EditDefaultsOnly, Category="Gunplay")
	FName LANLevel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Gunplay")
	FName DSLevel;
private:
	UFUNCTION()
	void OnSolitaryClicked();

	UFUNCTION()
	void OnLANClicked();
	void StartDSMode(UGunplayGameInstance* GameInstance) const;

	UFUNCTION()
	void OnDSClicked();
	
	void StartLANMode(UGunplayGameInstance* GunplayGameInstance) const;
};
