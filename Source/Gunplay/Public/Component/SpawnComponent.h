// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnComponent.generated.h"

/*
 * 让一个Actor具有被Spawn的功能, 需要配合Spawner
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUNPLAY_API USpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Spawner的类型
	
	
	USpawnComponent();

	FORCEINLINE void SetSpawner(class ASingleSpawner* TargetSpawner) { Spawner = TargetSpawner; }

	FORCEINLINE class ASingleSpawner* GetSpawner() const { return Spawner; }

	// 重置spawner，让spawner能够重新生成Actor
	UFUNCTION(BlueprintCallable, Category="Spawn")
	void ResetSpawner();

private:
	// the spawner that spawns this
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Target", meta=(AllowPrivateAccess="true"))
	class ASingleSpawner* Spawner;
};
