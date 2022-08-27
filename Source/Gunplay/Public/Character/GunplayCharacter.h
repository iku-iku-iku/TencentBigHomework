#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/AdsorbInterface.h"
#include "Interface/BeHitInterface.h"
#include "Interface/BeObtainedInterface.h"
#include "Net/UnrealNetwork.h"
#include "GunplayCharacter.generated.h"

DECLARE_EVENT_OneParam(AGunplayCharacter, FGunplayCharacterEvent, const AGunplayCharacter*);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterMultiDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneParamCharacterMultiDelegate, float, Delta);

UENUM()
enum class EGunplayCharacterType { Null, Player, Enemy };

UCLASS(config=Game)
class AGunplayCharacter : public ACharacter, public IBeHitInterface, public IAdsorbInterface
{
	GENERATED_BODY()

protected:
	AGunplayCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	// 状态
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	class UCharacterStatusComponent* StatusComponent;

	// 抓持
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Holding", meta=(AllowPrivateAccess="true"))
	class UHoldComponent* HoldingComponent;

	// 血条
	UPROPERTY(VisibleAnywhere)
	class UBloodBarComponent* BloodBarComponent;

	UPROPERTY()
	class UAnimationComponent* AnimationComponent;

	UPROPERTY(BlueprintReadWrite, Category=Jump)
	bool bJump;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hit")
	float BaseHitForceScale = .0f;

	UPROPERTY(EditDefaultsOnly, Category="IK")
	float MaxFootDetectDistance = 100.f;

	UPROPERTY(EditDefaultsOnly, Category="IK")
	float MaxHipOffset = 100.f;

	UPROPERTY(EditDefaultsOnly, Category="IK")
	FName LFootSocketName = TEXT("LFootSocket");

	UPROPERTY(EditDefaultsOnly, Category="IK")
	FName RFootSocketName = TEXT("RFootSocket");

	UPROPERTY(EditDefaultsOnly, Category="IK")
	float FootInterpolateSpeed = 20.f;

	UPROPERTY(EditDefaultsOnly, Category="Bone")
	FName HeadBoneName = TEXT("Head");
public:
	virtual EGunplayCharacterType GetType() const { return EGunplayCharacterType::Null; }

	virtual void Jump() override;

	FORCEINLINE const FName& GetHeadBoneName() const { return HeadBoneName; }

	FORCEINLINE void Die() { Destroy(); };

	FORCEINLINE FGunplayCharacterEvent& OnDeath() { return DeathEvent; }

	// 获取状态
	FORCEINLINE class UCharacterStatusComponent* GetStatus() const { return StatusComponent; }
	// 获取Holding
	FORCEINLINE class UHoldComponent* GetHoldingComponent() const { return HoldingComponent; }
	// 获取BloodBarComponent
	FORCEINLINE class UBloodBarComponent* GetBloodBarComponent() const { return BloodBarComponent; }

	FORCEINLINE class UAnimationComponent* GetAnimationComponent() const { return AnimationComponent; }

	FORCEINLINE float GetLFootOffset() const { return LFootOffset; }
	FORCEINLINE float GetRFootOffset() const { return RFootOffset; }
	FORCEINLINE float GetHipOffset() const { return HipOffset; }

	virtual void BeHit(const FHitInfo& HitInfo) override;

	bool ObtainHolding(const TSubclassOf<AActor> HoldingClass);

	template <typename T>
	T* Template_Obtain(const TSubclassOf<T> HoldingClass);

private:
	float LFootOffset, RFootOffset, HipOffset;

	FGunplayCharacterEvent DeathEvent;

	UFUNCTION()
	void OnRep_WantToJump();

	void TraceFoot(const FName& SocketName, float& OutFootOffset, FVector& OutHitLocation) const;

	void CalculateFootIK(const float DeltaSeconds);

protected:
	// 只在射击者的客户端进行的射击效果显示
	UFUNCTION(Client, Reliable)
	void Client_HitCharacterEffect(const FHitInfo& HitInfo);

	// hook functions : 被杀死
	virtual void BeKilledBy(const AController* Killer)
	{
	}

	virtual float DefenseScale();
};

template <typename T>
T* AGunplayCharacter::Template_Obtain(const TSubclassOf<T> HoldingClass)
{
	check(T::StaticClass()->IsChildOf(AActor::StaticClass()))

	if (UWorld* World = GetWorld())
	{
		if (T* Holding = World->SpawnActor<T>(HoldingClass))
		{
			if (Holding->template Implements<UBeObtainedInterface>())
			{
				IBeObtainedInterface::Execute_BeObtainedBy(Holding, this);
				return Holding;
			}
		}
	}
	return nullptr;
}
