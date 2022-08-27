// Copyright iku-iku-iku,. All Rights Reserved.


#include "Game/Solitary/ExtremeSurvivalGameMode.h"

#include "AI/EnemySpawner.h"
#include "Character/Enemy/EnemyCharacter.h"
#include "Component/CharacterStatusComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Game/WaveWidget.h"

void AExtremeSurvivalGameMode::OnEnemyDeath(const AGunplayCharacter* Enemy)
{
	RemainingEnemyCount--;
}

void AExtremeSurvivalGameMode::OnActorSpawned(AActor* SpawnedActor)
{
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SpawnedActor))
	{
		EnemyCharacter->OnDeath().AddUObject(this, &AExtremeSurvivalGameMode::OnEnemyDeath);
	}
	
	if (SpawnedActor->GetClass()->IsChildOf(AEnemyCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("检测到一个敌人生成了"))
	}
}

AExtremeSurvivalGameMode::AExtremeSurvivalGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AExtremeSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		// 注册OnActorSpawned多播事件
		const auto Delegate =
			FOnActorSpawned::FDelegate::CreateUObject(this, &AExtremeSurvivalGameMode::OnActorSpawned);
		World->AddOnActorSpawnedHandler(Delegate);

		// 收集EnemySpawner
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawner::StaticClass(), Actors);
		for (AActor* Actor : Actors)
		{
			if (AEnemySpawner* EnemySpawner = Cast<AEnemySpawner>(Actor))
			{
				EnemySpawners.Add(EnemySpawner);
			}
		}
	}


}

void AExtremeSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (RemainingEnemyCount <= 0 && EnemySpawners.Num() != 0)
	{
		StartNextWave();
	}
}

TSubclassOf<AEnemyCharacter> AExtremeSurvivalGameMode::GetRandomEnemyClass()
{
	const float Choice = FMath::FRand();
	TSubclassOf<AEnemyCharacter> EnemyClass;
	float ProbAcc = 0.f;
	for (const auto& Class2SpawnProbability : EnemyClass2SpawnProbability)
	{
		EnemyClass = Class2SpawnProbability.Key;
		ProbAcc += Class2SpawnProbability.Value;
		if (Choice < ProbAcc)
		{
			break;
		}
	}

	check(EnemyClass != nullptr);
	return EnemyClass;
}

void AExtremeSurvivalGameMode::StartNextWave()
{
	WaveCount++;

	FillEnemySpawnProbability();

	UE_LOG(LogTemp, Warning, TEXT("开始第%d波"), WaveCount)

	StartNextWaveEvent.Broadcast(WaveCount);

	RemainingEnemyCount = 0;

	const int32 EachSpawnerSpawnCount = GetMaxSpawnCount();
	const int32 WaveInterval = GetWaveInterval();
	for (AEnemySpawner* EnemySpawner : EnemySpawners)
	{
		EnemySpawner->SetSpawnCount(EachSpawnerSpawnCount);
		EnemySpawner->SetSpawnTimer(WaveInterval);

		RemainingEnemyCount += EachSpawnerSpawnCount;
	}

	if (const AGunplayCharacter* GunplayCharacter = Cast<AGunplayCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if (UCharacterStatusComponent* Status = GunplayCharacter->GetStatus())
		{
			Status->SetMaxHP(Status->GetMaxHP() + 50);
		}
	}
}

void AExtremeSurvivalGameMode::FillEnemySpawnProbability()
{
	float ProbSum = 0.f;
	EnemyClass2SpawnProbability.Empty();
	for (TSubclassOf<AEnemyCharacter> EnemyClass : EnemyClasses)
	{
		if (AEnemyCharacter* EnemyCDO = EnemyClass.GetDefaultObject())
		{
			float SpawnProbability = EnemyCDO->GetSpawnProbability(WaveCount);

			EnemyClass2SpawnProbability.Add(FClass2Float(EnemyClass, SpawnProbability));

			ProbSum += SpawnProbability;
		}
	}

	if (ProbSum > 1e-5)
	{
		// 归一化
		for (auto& Item : EnemyClass2SpawnProbability)
		{
			Item.Value /= ProbSum;
		}
	}
}
