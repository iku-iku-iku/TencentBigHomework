// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SingleSpawner.generated.h"

UCLASS()
class GUNPLAY_API ASingleSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Target Spawner", meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* Mesh;
public:
	ASingleSpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Target Spawner")
	float SpawnInterval = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Target Spawner")
	float SpawnHeight = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Target Spawner")
	TSubclassOf<AActor> TargetToSpawn;

	UFUNCTION(BlueprintCallable, Category="Target Spawner")
	void SpawnTarget();

public:
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetEmpty() { Empty = true; }


private:
	float SpawnTimer = 0;

	// 当前没有生成的靶子
	bool Empty = true;
};
