// Copyright iku-iku-iku,. All Rights Reserved.


#include "Character/Enemy/SneakEnemy.h"

#include "TimerManager.h"
#include "Component/BloodBarComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Holding/Hands.h"

void ASneakEnemy::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogEnemy, Warning, TEXT("一个SneakEnemy加入战场"))

	ObtainHolding(HandClass);

	Sneak();
}

float ASneakEnemy::GetSpawnProbabilityWithoutDeviation(int32 WaveCount)
{
	if (WaveCount <= 3) return 0;
	return FMath::Max(0.5f, 1 - 2.0f * WaveCount / 20);
}

void ASneakEnemy::BeHit(const FHitInfo& HitInfo)
{
	Super::BeHit(HitInfo);

	Reveal();

	GetWorld()->GetTimerManager().SetTimer(SneakTimer, [this] { Sneak(); }, RevealDurationWhenHit, false);
}

void ASneakEnemy::Sneak() const
{
	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		MeshComponent->SetRenderInMainPass(false);
		MeshComponent->SetLightingChannels(false, true, false);
	}

	BloodBarComponent->SetHiddenInGame(true);
}

void ASneakEnemy::Reveal() const
{
	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		MeshComponent->SetRenderInMainPass(true);
		MeshComponent->SetLightingChannels(true, false, false);
	}

	BloodBarComponent->SetHiddenInGame(false);
}
