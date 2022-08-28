// Copyright iku-iku-iku,. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/BeObtainedInterface.h"
#include "Interface/UseInterface.h"
#include "Holding.generated.h"

UCLASS()
class GUNPLAY_API AHolding : public AActor, public IUseInterface, public IBeObtainedInterface
{
	GENERATED_BODY()

public:
	AHolding();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Use() override
	{
	}

	virtual void Using(float DeltaTime) override
	{
	}

	virtual void Used() override
	{
	}

	virtual void BeObtainedBy_Implementation(AGunplayCharacter* GunplayCharacter) override;

	FORCEINLINE class AGunplayCharacter* GetHolder() const { return Holder; }


protected:
	UPROPERTY(Replicated)
	class AGunplayCharacter* Holder;
};
