// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/ShootComponent.h"

#include <Engine/World.h>

#include "Camera/CameraComponent.h"
#include "Character/GunplayCharacter.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Component/BeadComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interface/ShootInterface.h"
#include "Util/GunplayUtils.h"

UShootComponent::UShootComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ShootTimer -= DeltaTime;
}

bool UShootComponent::ShootDetect(const FVector& Start, const FVector& End, FHitResult& OutHit,
<<<<<<< HEAD
                                  const ECollisionChannel ShootChannel,
                                  const AActor* IgnoredActor) const
{
	FCollisionQueryParams CollisionQueryParams;

	// 防止射中发射者
=======
                                  const AActor* IgnoredActor, TSubclassOf<AActor> IgnoredClass) const
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionQueryParams;
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	if (IgnoredActor)
	{
		CollisionQueryParams.AddIgnoredActor(IgnoredActor);
	}

<<<<<<< HEAD
	return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ShootChannel, CollisionQueryParams);
=======
	GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_GUN, CollisionQueryParams);

	for (FHitResult HitResult : HitResults)
	{
		if (const AActor* HitActor = HitResult.GetActor())
		{
			if (IgnoredClass && HitActor->GetClass()->IsChildOf(IgnoredClass))
			{
				continue;
			}

			OutHit = HitResult;
			return true;
		}
	}
	return false;
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
}

void UShootComponent::GetPlayerShootLine(FVector& Start, FVector& End, const APlayerCharacter* PlayerCharacter) const
{
	// 进行准星射击
	if (UBeadComponent* BeadComponent = GunplayUtils::GetComponent<UBeadComponent>(GetOwner()))
	{
		BeadComponent->BeadShoot();

		// 在准星范围内找一个射击点
		FVector WorldLocation, WorldDirection;
		BeadComponent->GetBeadRandPoint(WorldLocation, WorldDirection);

		Start = PlayerCharacter->GetFollowCamera()->GetComponentLocation();
		Start += WorldDirection * PlayerCharacter->GetCameraBoom()->TargetArmLength;

		End = WorldLocation + WorldDirection * GetShootRange();
	}
}

void UShootComponent::GetEnemyShootLine(FVector& Start, FVector& End, const AEnemyCharacter* EnemyCharacter) const
{
	const FVector ForwardDir = EnemyCharacter->GetAttackForward();
	Start = EnemyCharacter->GetActorLocation();
	End = Start + ForwardDir * GetShootRange();
}

void UShootComponent::Shoot(const AGunplayCharacter* Shooter)
{
	FHitResult HitResult;

	if (Shooter)
	{
		FVector Start, End;

		if (Shooter->GetType() == EGunplayCharacterType::Player)
		{
			GetPlayerShootLine(Start, End, Cast<APlayerCharacter>(Shooter));
<<<<<<< HEAD
			ShootDetect(Start, End, HitResult, ECC_Player_Shoot, Shooter);
=======
			ShootDetect(Start, End, HitResult, Shooter);
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
		}
		else if (Shooter->GetType() == EGunplayCharacterType::Enemy)
		{
			GetEnemyShootLine(Start, End, Cast<AEnemyCharacter>(Shooter));
<<<<<<< HEAD
			ShootDetect(Start, End, HitResult, ECC_Enemy_Shoot, Shooter);
		}
	}
	
=======
			ShootDetect(Start, End, HitResult, Shooter, AEnemyCharacter::StaticClass());
		}
	}
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
	Server_Shoot(HitResult);
}

void UShootComponent::Server_Shoot_Implementation(const FHitResult& HitResult)
{
	if (IShootInterface* ShootInterface = Cast<IShootInterface>(GetOwner()))
	{
		if (ShootInterface->Server_Shoot(HitResult))
		{
			Multi_Shoot(HitResult);
		}
	}
}

void UShootComponent::Shooting(const AGunplayCharacter* Shooter)
{
	if (ShootTimer < 0)
	{
		Shoot(Shooter);
		ShootTimer = GetShootInterval();
	}
}

void UShootComponent::Multi_Shoot_Implementation(const FHitResult& HitResult)
{
	if (IShootInterface* ShootInterface = Cast<IShootInterface>(GetOwner()))
	{
		ShootInterface->Multi_ShootEffect(HitResult);
	}
}
