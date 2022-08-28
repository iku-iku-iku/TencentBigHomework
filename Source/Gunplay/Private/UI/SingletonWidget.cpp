// Copyright iku-iku-iku,. All Rights Reserved.


#include "UI/SingletonWidget.h"

#include "Game/GunplayGameInstance.h"

void USingletonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UGunplayGameInstance::AddSingleton(this);
}
