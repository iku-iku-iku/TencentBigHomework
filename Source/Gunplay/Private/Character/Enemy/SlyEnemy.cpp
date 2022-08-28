// Copyright iku-iku-iku,. All Rights Reserved.


#include "Character/Enemy/SlyEnemy.h"

#include "Holding/Gun.h"
#include "Interface/BeObtainedInterface.h"

void ASlyEnemy::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogEnemy, Warning, TEXT("一个SlyEnemy加入战场"))

	if (AGun* Gun = Template_Obtain(GunClass))
	{
		Gun->SetBulletNum(INT_MAX);
		Gun->SetMaxBullet(INT_MAX);
	}
}

float ASlyEnemy::GetSpawnProbabilityWithoutDeviation(int32 WaveCount)
{
	return FMath::Min(0.3f, WaveCount * 1.0f / 10.f);
}
