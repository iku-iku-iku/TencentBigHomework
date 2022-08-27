// Copyright iku-iku-iku,. All Rights Reserved.


#include "Animation/GunplayCharacterAnimation.h"

#include "Character/GunplayCharacter.h"
#include "Character/Player/PlayerCharacter.h"
#include "Component/AnimationComponent.h"
#include "Component/HoldComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Holding/Grenade.h"
#include "Holding/Gun.h"


void UGunplayCharacterAnimation::AnimNotify_ThrowGrenade() const
{
	UE_LOG(LogTemp, Warning, TEXT("Notify"))

	if (OwningCharacter)
	{
		if (const UHoldComponent* HoldingComponent = OwningCharacter->GetHoldingComponent())
		{
			if (AGrenade* Grenade = Cast<AGrenade>(HoldingComponent->GetCurrentHolding()))
			{
				Grenade->ThrowGrenade();
			}
		}
	}
}

void UGunplayCharacterAnimation::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	if (AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(GetOwningActor()))
	{
		OwningCharacter = GunplayCharacter;
	}
}

void UGunplayCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningCharacter)
	{
		LFootEffectorLocation = {OwningCharacter->GetLFootOffset() * -1.f, 0, 0};
		RFootEffectorLocation = {OwningCharacter->GetRFootOffset(), 0, 0};
		HipTranslation = {0, 0, OwningCharacter->GetHipOffset()};

		if (UAnimationComponent* AnimationComponent = OwningCharacter->GetAnimationComponent())
		{
			bInAir = AnimationComponent->IsInAir();
			bIsShooting = AnimationComponent->IsShooting();
			bJump = AnimationComponent->ConsumeWanToJump();

			// 针对玩家角色的设定
			if (const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OwningCharacter))
			{
				VerticalOrientation = AnimationComponent->GetVerticalOrientation();
				HorizontalOrientation = AnimationComponent->GetHorizontalOrientation();
				bIsAiming = AnimationComponent->IsAiming();
			}
		}

		const FVector Velocity = OwningCharacter->GetVelocity();
		const FRotator ActorRotation = OwningCharacter->GetActorRotation();
		Direction = CalculateDirection(Velocity, ActorRotation);
		Speed = Velocity.Size();

		bHoldingGun = false;
		if (const UHoldComponent* HoldingComponent = OwningCharacter->GetHoldingComponent())
		{
			if (AActor* CurrentHolding = HoldingComponent->GetCurrentHolding())
			{
				if (const AGun* Gun = Cast<AGun>(CurrentHolding))
				{
					bHoldingGun = true;
					BarrelLocation = Gun->GetBarrelLocation();
					BarrelLocation -= HipTranslation;
				}
			}
		}

		bIsStatic = OwningCharacter->GetVelocity().Size() < StaticTolerance;
	}
}
