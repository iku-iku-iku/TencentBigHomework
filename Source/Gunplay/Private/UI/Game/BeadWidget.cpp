// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/Game/BeadWidget.h"

#include <DrawDebugHelpers.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>

#include "Component/BeadComponent.h"
#include "Component/HoldComponent.h"
#include "Component/ShootComponent.h"
#include "Components/TextBlock.h"
#include "Game/GunplayPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Util/GunplayUtils.h"

namespace
{
	const FVector2D Up(0.f, -1.f);
	const FVector2D Down(0.f, 1.f);
	const FVector2D Left(-1.f, 0.f);
	const FVector2D Right(1.f, 0.f);
}

void UBeadWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetAllBeadPosition();
}

void UBeadWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitialCenterTranslation = CenterBead->RenderTransform.Translation;
}

void UBeadWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ShootOffset > 0.f)
	{
		// 准星偏移越大，回缩越快
		const float SpeedUpRate = GetTotalRadius() / (BaseRadius + BaseOffset);
		AddShootOffset(-ShrinkRate * InDeltaTime * SpeedUpRate);
	}

	UpdateBeadStatus();
}

void UBeadWidget::GetRandomPoint(FVector& WorldLocation, FVector& WorldDirection)
{
	const FVector2D RandCircularDir = {
		FMath::Cos(FMath::RandRange(0.f, 360.f)),
		FMath::Sin(FMath::RandRange(0.f, 360.f))
	};
	const float RandDist = FMath::RandRange(0.f, GetRadius());

	const FVector2D RandCoordinate = RandCircularDir * RandDist;

	Coord2WorldSpace(RandCoordinate, WorldLocation, WorldDirection, CenterBead);
}

void UBeadWidget::Coord2WorldSpace(const FVector2D& Coord, FVector& WorldLocation, FVector& WorldDirection,
                                   UWidget* Widget) const
{
	if (const APlayerController* PlayerController = GetOwningPlayer())
	{
		const FVector2D ScreenPos = GunplayUtils::WidgetCoordinate2Viewport(Widget, Coord);
		PlayerController->DeprojectScreenPositionToWorld(ScreenPos.X, ScreenPos.Y, WorldLocation,
		                                                 WorldDirection);
	}
}

void UBeadWidget::SetAdsorbEnable(bool bEnable)
{
	bEnableAdsorb = bEnable;
	CenterBead->SetRenderTranslation(InitialCenterTranslation);
}

void UBeadWidget::SetBeadPosition(UWidget* Widget, const FVector2D& Dir) const
{
	Widget->SetRenderTranslation(CenterBead->RenderTransform.Translation + GetTotalRadius() * Dir);
}

void UBeadWidget::AutoAdsorb()
{
	if (CanAdsorb(FVector2D::ZeroVector))
	{
		return;
	}

	TArray<float> SamplePoints = GunplayUtils::LineSpace(0.f, 360.f, 10, false);

	for (const float Theta : SamplePoints)
	{
		// 在一定范围内能击中目标则不收回准星
		const FVector2D Coord = GetRadius() * FVector2D(FMath::Cos(Theta), FMath::Sin(Theta));
		if (CanAdsorb(Coord))
		{
			return;
		}
	}

	bool bCanAdsorb = false;
	for (const float Theta : SamplePoints)
	{
		const FVector2D Coord = (GetRadius() + AdsorbRadiusOffset) * FVector2D(FMath::Cos(Theta), FMath::Sin(Theta));

		if (CanAdsorb(Coord))
		{
			const FVector2D AdsorbPos = GunplayUtils::WidgetCoordinate2Viewport(CenterBead, Coord);
			const FVector2D CenterPos = GunplayUtils::WidgetCoordinate2Viewport(CenterBead, {0.f, 0.f});
			const FVector2D NewTranslation = CenterBead->RenderTransform.Translation + (AdsorbPos - CenterPos);

			if ((NewTranslation - InitialCenterTranslation).Size() < AdsorbRadiusOffset + GetPureRadius())
			{
				CenterBead->SetRenderTranslation(NewTranslation);
				bCanAdsorb = true;
			}

			break;
		}
	}

	// 如果不能吸附则直接收回
	if (! bCanAdsorb)
	{
		CenterBead->SetRenderTranslation(InitialCenterTranslation);
	}
}

bool UBeadWidget::CanAdsorb(const FVector2D Coord) const
{
	if (const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		if (const UHoldComponent* HoldingComponent = PlayerCharacter->GetHoldingComponent())
		{
			if (const AActor* CurrentHolding = HoldingComponent->GetCurrentHolding())
			{
				if (const UShootComponent* ShootComponent = GunplayUtils::GetComponent_Const<UShootComponent>(
					CurrentHolding))
				{
					FVector WorldLocation, WorldDirection;

					Coord2WorldSpace(Coord, WorldLocation, WorldDirection, CenterBead);

					FVector Start = PlayerCharacter->GetFollowCamera()->GetComponentLocation();
					Start += WorldDirection * PlayerCharacter->GetCameraBoom()->TargetArmLength;
					const FVector End = WorldLocation + WorldDirection * ShootComponent->GetShootRange();

					FHitResult HitResult;
					if (ShootComponent->ShootDetect(Start, End, HitResult, ECC_Player_Shoot, PlayerCharacter))
					{
						if (const IAdsorbInterface* AdsorbInterface = Cast<IAdsorbInterface>(HitResult.GetActor()))
						{
							return AdsorbInterface->CanAdsorb();
						}
					}
				}
			}
		}
	}
	return false;
}

void UBeadWidget::SetAllBeadPosition() const
{
	SetBeadPosition(UpBead, Up);
	SetBeadPosition(DownBead, Down);
	SetBeadPosition(LeftBead, Left);
	SetBeadPosition(RightBead, Right);
}

void UBeadWidget::UpdateBeadStatus()
{
	bool bCanShowBead = false;

	if (const APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		if (const UHoldComponent* HoldingComponent = PlayerCharacter->GetHoldingComponent())
		{
			if (const AActor* CurrentHolding = HoldingComponent->GetCurrentHolding())
			{
				if (UBeadComponent* BeadComponent = GunplayUtils::GetComponent<UBeadComponent>(CurrentHolding))
				{
					bCanShowBead = true;
					ShowBead();

					if (bEnableAdsorb)
					{
						AutoAdsorb();
					}

					SetBaseRadius(BeadComponent->GetBaseRadius());
					AddShootOffset(BeadComponent->ConsumeShootOffset());
				}
			}
		}
	}
	if (! bCanShowBead)
	{
		HideBead();
	}
}
