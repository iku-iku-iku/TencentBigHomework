// Copyright iku-iku-iku,. All Rights Reserved.


#include "Holding/Hands.h"

#include "Animation/AnimInstance.h"
#include "Character/GunplayCharacter.h"
#include "Component/HoldComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AHands::AHands()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
}

void AHands::Use()
{
	Server_Punch();
}

void AHands::Using(float DeltaTime)
{
}

void AHands::Used()
{
}

void AHands::BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter)
{
	Super::BeObtainedBy_Implementation(GunplayCharacter);

	check(HasAuthority())

	if (GunplayCharacter)
	{
		if (UHoldComponent* HoldingComponent = GunplayCharacter->GetHoldingComponent())
		{
			HoldingComponent->AddHolding(this);
		}
		if (const USkeletalMeshComponent* SkeletalMeshComponent = Holder->GetMesh())
		{
			if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
			{
				HolderAnimInstance = AnimInstance;
			}
		}
	}
}

void AHands::Server_Punch_Implementation()
{
	if (HolderAnimInstance && !HolderAnimInstance->Montage_IsPlaying(Montage_Boxing))
	{
		Multi_Punch();
		AlreadyHitActors.Empty();
		bFirstTraceInOnePunch = true;
		TraceHit();
	}
}

void AHands::Multi_Punch_Implementation()
{
	if (Holder)
	{
		if (const USkeletalMeshComponent* SkeletalMeshComponent = Holder->GetMesh())
		{
			if (UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance())
			{
				AnimInstance->Montage_Play(Montage_Boxing);
				if (PunchSound && Holder)
				{
					const FVector Location = Holder->GetActorLocation();
					UGameplayStatics::PlaySoundAtLocation(this, PunchSound, Location);
				}
			}
		}
	}
}

bool AHands::AllowHit_Implementation(AActor* HitActor)
{
	return true;
}

void AHands::TraceHit()
{
	if (!HolderAnimInstance || !HolderAnimInstance->Montage_IsPlaying(Montage_Boxing))
	{
		return;
	}

	if (const USkeletalMeshComponent* SkeletalMeshComponent = Holder->GetMesh())
	{
		const FVector TraceSocketLocation = SkeletalMeshComponent->GetSocketLocation(TraceSocket);

		if (const UWorld* World = GetWorld())
		{
			FHitResult HitResult;

			const FCollisionShape Sphere = FCollisionShape::MakeSphere(HitRadius);

			FCollisionQueryParams CollisionQueryParams;
			CollisionQueryParams.AddIgnoredActor(Holder);

			if (!bFirstTraceInOnePunch)
			{
				if (World->SweepSingleByChannel(HitResult, TraceSocketLocation, TraceSocketLocation, FQuat::Identity,
				                                ECC_WorldDynamic, Sphere, CollisionQueryParams))
				{
					AActor* HitActor = HitResult.GetActor();
					if (!AlreadyHitActors.Contains(HitActor) && AllowHit(HitActor))
					{
						AlreadyHitActors.Add(HitActor);

						if (IBeHitInterface* BeHitInterface = Cast<IBeHitInterface>(HitActor))
						{
							const FVector Speed = (TraceSocketLocation - LastSocketLocation) / HitTraceInterval;
							const FVector Impulse = Speed * ImpulseScale;
							FHitInfo HitInfo(Holder->GetController(), Holder, Impulse, HitResult.Location, Damage);
							BeHitInterface->BeHit(HitInfo);
						}
					}
				}
			}
			LastSocketLocation = TraceSocketLocation;
		}
	}

	bFirstTraceInOnePunch = false;
	// 间隔一定时间再次trace
	GetWorldTimerManager().SetTimer(HitTraceTimerHandle, this, &AHands::TraceHit, HitTraceInterval);
}
