#pragma once
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/Widget.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// UI
namespace GunplayUtils
{
	inline FVector2D GetWidgetCenterPosition(UWidget* Widget)
	{
		if (Widget == nullptr) { return {}; }

		FVector2D PixelPosition, ViewportPosition;
		const FVector2D WidgetSize = Widget->GetCachedGeometry().Size;

		USlateBlueprintLibrary::LocalToViewport(Widget, Widget->GetCachedGeometry(), WidgetSize / 2, PixelPosition,
		                                        ViewportPosition);

		return PixelPosition;
	}

	inline FVector2D WidgetCoordinate2Viewport(UWidget* Widget, const FVector2D& Coordinate)
	{
		if (Widget == nullptr) { return {}; }

		FVector2D PixelPosition, ViewportPosition;
		const FVector2D WidgetSize = Widget->GetCachedGeometry().Size;

		USlateBlueprintLibrary::LocalToViewport(Widget, Widget->GetCachedGeometry(), WidgetSize / 2 + Coordinate,
		                                        PixelPosition,
		                                        ViewportPosition);

		return PixelPosition;
	}
}

// Random
namespace GunplayUtils
{
	inline float RandDeviation(float Deviation)
	{
		if (Deviation < 0.f)
		{
			Deviation = -Deviation;
		}
		return FMath::RandRange(-Deviation, Deviation);
	}

	inline FRotator RandYawRotator()
	{
		return FRotator(0.f, RandDeviation(180.f), 0.f);
	}

	inline FVector RandGroundOffset(const float Deviation)
	{
		return FVector(RandDeviation(Deviation), RandDeviation(Deviation), 0.f);
	}

	inline FVector RandOffset(const float Deviation)
	{
		return FVector(RandDeviation(Deviation), RandDeviation(Deviation), RandDeviation(Deviation));
	}

	inline FVector FRandVector()
	{
		return FVector(FMath::FRand(), FMath::FRand(), FMath::FRand());
	}
}

// template
namespace GunplayUtils
{
	template <typename T>
	T* GetComponent(const class AActor* Actor)
	{
		return Cast<T>(Actor->GetComponentByClass(T::StaticClass()));
	}

	template <typename T>
	const T* GetComponent_Const(const class AActor* Actor)
	{
		return Cast<T>(Actor->GetComponentByClass(T::StaticClass()));
	}

	template <typename Class>
	Class* GetActorOfClass(const UObject* WorldContextObject)
	{
		return Cast<Class>(UGameplayStatics::GetActorOfClass(WorldContextObject, Class::StaticClass()));
	}

	template <typename Class>
	void GetAllActorsOfClassChecked(const UObject* WorldContextObject, TArray<Class*>& OutActors)
	{
		TArray<AActor*> TempOutActors;
		UGameplayStatics::GetAllActorsOfClass(WorldContextObject, Class::StaticClass(), TempOutActors);
		for (AActor* TempOutActor : TempOutActors)
		{
			if (Class* Actor = Cast<Class>(TempOutActor))
			{
				OutActors.Add(Actor);
			}
		}
	}

	template <typename Elem>
	Elem& RandChoice(TArray<Elem>& Arr)
	{
		check(Arr.Num() != 0)
		return Arr[FMath::RandRange(0, Arr.Num() - 1)];
	}
};

// math
namespace GunplayUtils
{
	inline TArray<float> LineSpace(float Min, float Max, int Num, const bool bIncludeMax)
	{
		if (bIncludeMax) { Num--; }

		TArray<float> Results;

		const float Interval = (Max - Min) / Num;
		for (int i = 0; i < Num; i++)
		{
			Results.Add(Min + Interval * i);
		}

		if (bIncludeMax)
		{
			Results.Add(Max);
		}
		
		return Results;
	}
}

// time
namespace GunplayUtils
{
	inline void UntilDo(UWorld* World, TFunction<bool()>&& Until, TFunction<void()>&& Do,
	                    const float CheckRate = 0.2f)
	{
		if (World)
		{
			if (Until())
			{
				Do();
				return;
			}
			FTimerHandle TimerHandle;
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([World, &TimerHandle, &TimerDelegate, CheckRate, Do, Until]
				{
					if (Until())
					{
						Do();
					}
					else
					{
						World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, CheckRate, false);
					}
				}
			);
			World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, CheckRate, false);
		}
	}
}
