// Copyright iku-iku-iku,. All Rights Reserved.


#include "Component/ProjectileComponent.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Character/GunplayCharacter.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Util/GunplayUtils.h"

UProjectileComponent::UProjectileComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UProjectileComponent::Project(const AGunplayCharacter* Projector)
{
	check(Projector != nullptr)
	AActor* Owner = GetOwner();
	check(Owner != nullptr)

	if (bHasBeenProjected) { return; }
	bHasBeenProjected = true;

	FVector Forward;
	if (Projector->GetType() == EGunplayCharacterType::Player)
	{
		if (const UCameraComponent* CameraComponent = Cast<UCameraComponent>(
			Projector->GetComponentByClass(UCameraComponent::StaticClass())))
		{
			Forward = CameraComponent->GetForwardVector();
		}
	}
	else if (Projector->GetType() == EGunplayCharacterType::Enemy)
	{
		const AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Projector);

		Forward = EnemyCharacter->GetAttackForward();
	}

	const FVector ProjectDirection = (Forward + FVector::UpVector * ProjectHeightScale).GetSafeNormal();

	Owner->SetActorLocation(Owner->GetActorLocation() + ProjectDirection * ProjectStartOffset);
	if (UMeshComponent* Mesh = GunplayUtils::GetComponent<UMeshComponent>(Owner))
	{
		Mesh->AddImpulse(ProjectDirection * BaseProjectForce);
	}
}

void UProjectileComponent::Montage_StartProject(const AGunplayCharacter* Projector) const
{
	if (const USkeletalMeshComponent* SkeletalMeshComponent = Projector->GetMesh())
	{
		if (UAnimInstance* AnimInst = SkeletalMeshComponent->GetAnimInstance())
		{
			if (! AnimInst->Montage_IsPlaying(Montage_ThrowGrenade))
			{
				UE_LOG(LogTemp, Warning, TEXT("Start Montage"))

				AnimInst->Montage_Play(Montage_ThrowGrenade);
			}
		}
	}
}

void UProjectileComponent::Montage_EndProject(const AGunplayCharacter* Projector) const
{
	if (const USkeletalMeshComponent* SkeletalMeshComponent = Projector->GetMesh())
	{
		if (UAnimInstance* AnimInst = SkeletalMeshComponent->GetAnimInstance())
		{
			if (AnimInst->Montage_IsPlaying(Montage_ThrowGrenade) &&
				! AnimInst->Montage_GetCurrentSection(Montage_ThrowGrenade).IsEqual(TEXT("ThrowEnd")))
			{
				UE_LOG(LogTemp, Warning, TEXT("End Montage"))

				AnimInst->Montage_JumpToSection(TEXT("ThrowEnd"), Montage_ThrowGrenade);
			}
		}
	}
}
