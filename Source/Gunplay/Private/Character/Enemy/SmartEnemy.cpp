// Copyright iku-iku-iku,. All Rights Reserved.


#include "Character/Enemy/SmartEnemy.h"
#include "Engine/World.h"
#include "Holding/Hands.h"
#include "Holding/Gun.h"

void ASmartEnemy::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogEnemy, Warning, TEXT("一个SmartEnemy加入战场"))


	if (AGun* Gun = Template_Obtain(GunClass))
	{
		Gun->SetBulletNum(INT_MAX);
		Gun->SetMaxBullet(INT_MAX);
	}

	ObtainHolding(HandClass);
}

float ASmartEnemy::GetSpawnProbabilityWithoutDeviation(int32 WaveCount)
{
	if (WaveCount <= 5) return 0;
	return FMath::Min(0.2f, 1.f * WaveCount / 5);
}
