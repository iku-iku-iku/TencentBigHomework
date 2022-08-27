// Copyright iku-iku-iku,. All Rights Reserved.


#include "Character/Enemy/GunEnemy.h"

#include "Holding/Gun.h"


void AGunEnemy::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogEnemy, Warning, TEXT("一个GunEnemy加入战场"))

	if (AGun* Gun = Template_Obtain(GunClass))
	{
		Gun->SetBulletNum(INT_MAX);
		Gun->SetMaxBullet(INT_MAX);
	}
}

float AGunEnemy::GetSpawnProbabilityWithoutDeviation(int32 WaveCount)
{
	return FMath::Max(0.6f, 1 - WaveCount * 1.0f / 15.f);
}
