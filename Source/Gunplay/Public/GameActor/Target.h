#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/AdsorbInterface.h"
#include "Interface/BeHitInterface.h"
#include "Target.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeHitEvent, class ATarget*, BeHitTarget);

UENUM()
enum class ETargetPhysics { Null, Init, Hit };

UCLASS()
class GUNPLAY_API ATarget : public AActor, public IBeHitInterface, public IAdsorbInterface
{
	GENERATED_BODY()

public:
	ATarget();

	UFUNCTION(BlueprintPure, Category="Target")
	class USpawnComponent* GetSpawnComponent() const { return SpawnComponent; }

protected:
	virtual bool CanAdsorb() const override;
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY()
	class USpawnComponent* SpawnComponent;

	UPROPERTY(EditDefaultsOnly)
	class UIconComponent* IconComponent;

	UPROPERTY(ReplicatedUsing=OnRep_Physics)
	ETargetPhysics TargetPhysics = ETargetPhysics::Null;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	float MoveRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	float RotateRate;

	UPROPERTY(BlueprintAssignable, Category="Target")
	FBeHitEvent BeHitFirstTimeDelegate;

	// 被击中时的效果，蓝图中实现
	UFUNCTION(BlueprintImplementableEvent, Category="Target")
	void EffectWhenHitBy(class AGunplayPlayerController* Hitter);

	UFUNCTION()
	void OnRep_Physics();

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

	FORCEINLINE FBeHitEvent& GetBeHitFirstTimeDelegate() { return BeHitFirstTimeDelegate; }

	/* 被枪或手雷等武器击中
	 * 开启被击中时的物理模拟效果
	 * 第一次被击中后触发相应的效果
	 */
	UFUNCTION()
	void BeHitFirstTime(class AGunplayPlayerController* HitterPlayer);

	// 初始物理表现
	void SetInitialPhysics() const;

	// 被击中的物理表现
	void SetHitPhysics() const;

	virtual void BeHit(const FHitInfo& HitInfo) override;
};
