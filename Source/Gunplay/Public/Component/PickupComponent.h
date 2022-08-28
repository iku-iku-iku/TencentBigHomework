// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/GunplayCharacter.h"
#include "Components/SceneComponent.h"
#include "PickupComponent.generated.h"


/*
 * 让一个Actor具有被捡起的功能
 *
 * Holding需要实现IBeObtainedInterface接口
 * 该接口需要提供:
 * void BeObtainedBy(class class AGunplayCharacter* Character);
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API UPickupComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPickupComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup")
	class UBoxComponent* PickupTrigger;

public:
	// set the socket name that the actor can be attached to
	FORCEINLINE void SetSocketName(const FName Name) { SocketName = Name; }

	// get the character who owns the actor
	FORCEINLINE class AGunplayCharacter* GetOwnerCharacter() const { return OwnerPlayer; }

	// detach the actor from player
	UFUNCTION(BlueprintCallable, Category="Pickup")
	void DetachFromPlayer();

	// attach the actor to player
	UFUNCTION(BlueprintCallable, Category="Pickup")
	void AttachToPlayer(class AGunplayCharacter* Player);

	// set whether the actor can be picked up
	UFUNCTION(BlueprintCallable, Category="Pickup")
	void SetPickable(bool bPickable) const;

	// set whether simulating physics
	UFUNCTION(BlueprintCallable, Category="Pickup")
	void SetSimulatePhysics(bool bNewSimulatePhysics);

	UPROPERTY(ReplicatedUsing=OnRep_bSimulatePhysics)
	bool bSimulatePhysics = true;

	UFUNCTION()
	void OnRep_bSimulatePhysics() const;
private:
	FName SocketName;

	UPROPERTY(Replicated, VisibleAnywhere, Category="Pickup")
	class AGunplayCharacter* OwnerPlayer;

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
};
