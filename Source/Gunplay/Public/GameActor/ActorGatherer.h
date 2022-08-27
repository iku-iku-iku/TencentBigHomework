// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorGatherer.generated.h"

UCLASS()
class GUNPLAY_API AActorGatherer : public AActor
{
	GENERATED_BODY()

public:
	AActorGatherer();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) ;

	UPROPERTY(BlueprintReadWrite, Category="Gather")
	TArray<AActor*> GatheredActors;

	// 在此区域内的Actor能被检测到
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gather")
	class USphereComponent* SphereVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gather")
	TSubclassOf<AActor> TargetActorClass;

	UFUNCTION(BlueprintImplementableEvent, Category="Gather")
	void ProcessNewGatheredActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Gather")
	void UpdateGatheredActors();
};
