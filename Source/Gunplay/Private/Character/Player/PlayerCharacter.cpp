// Copyright iku-iku-iku,. All Rights Reserved.


#include "Character/Player/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Component/AnimationComponent.h"
#include "Component/BloodBarComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
<<<<<<< HEAD
#include "Component/HoldComponent.h"
=======
#include "Component/HoldingComponent.h"
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc
#include "Components/SkeletalMeshComponent.h"
#include "Game/GunplayPlayerController.h"
#include "Game/Online/OnlinePlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Holding/Gun.h"
#include "Holding/Hands.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	Tags.Add(TEXT("Player"));

	bReplicates = true;
	SetReplicatingMovement(true);
}

AOnlinePlayerState* APlayerCharacter::GetState() const
{
	return Cast<AOnlinePlayerState>(GetPlayerState());
}

AGunplayPlayerController* APlayerCharacter::GetPlayerController() const
{
	return Cast<AGunplayPlayerController>(Controller);
}

void APlayerCharacter::LookUp(float Val)
{
	SetOrientation();

	float Input = Val;
	if (AGunplayPlayerController* GunplayPlayerController = GetPlayerController())
	{
		Input *= GetPlayerController()->GetLookUpSensitivity() + 0.5f;
	}

	AddControllerPitchInput(Input);
}

void APlayerCharacter::Turn(float Val)
{
	SetOrientation();

	if (fabs(HorizontalOrientation) < 1.f || Val * HorizontalOrientation < 0.f)
	{
		float Input = Val;
		if (AGunplayPlayerController* GunplayPlayerController = GetPlayerController())
		{
			Input *= GetPlayerController()->GetTurnSensitivity() + 0.5f;
		}

		AddControllerYawInput(Input);
	}
}

void APlayerCharacter::MobileLookUp(float Val)
{
	PitchInput = Val;
	if (++InputCount < 2) { return; }
	InputCount = 0;

	if (HasRotationInput())
	{
		if (! bRotating)
		{
			StartRotationInput();
		}
	}
	else
	{
		bRotating = false;
		return;
	}

	SetOrientation();

	SetCharacterRotationWithInput();
}

void APlayerCharacter::MobileTurn(float Val)
{
	YawInput = Val;
	if (++InputCount < 2) { return; }
	InputCount = 0;

	if (HasRotationInput())
	{
		if (! bRotating)
		{
			StartRotationInput();
		}
	}
	else
	{
		bRotating = false;
		return;
	}

	SetOrientation();

	SetCharacterRotationWithInput();
}

void APlayerCharacter::StartRotationInput()
{
	BaseRotation = GetControlRotation();
	BaseYawInput = YawInput;
	BasePitchInput = PitchInput;
	bRotating = true;
}

void APlayerCharacter::SetOrientation()
{
	const float ControlYaw = GetControlRotation().Yaw;
	const float Yaw = GetActorRotation().Yaw;
	HorizontalOrientation = (FMath::Fmod(ControlYaw - Yaw + 540.f, 360.f) - 180.f) / 90.f;

	AnimationComponent->SetHorizontalOrientation(HorizontalOrientation);

	const float ControlPitch = GetControlRotation().Pitch;
	VerticalOrientation = (FMath::Fmod(ControlPitch + 540.f, 360.f) - 180.f) / 90.f;

	AnimationComponent->SetVerticalOrientation(VerticalOrientation);
}

void APlayerCharacter::SetCharacterRotationWithInput()
{
	const float PurePitchInput = PitchInput - BasePitchInput;
	const float PureYawInput = YawInput - BaseYawInput;
	const float TurnSensitivity = GetPlayerController()->GetTurnSensitivity();
	const float LookUpSensitivity = GetPlayerController()->GetLookUpSensitivity();
	const float Pitch = 90.f * PurePitchInput * (LookUpSensitivity + 0.5f);
	const float Yaw = 90.f * PureYawInput * (LookUpSensitivity + 0.5f);
	const FRotator NewRotator = BaseRotation + FRotator(Pitch, Yaw, 0.f);
	GetPlayerController()->SetControlRotation(NewRotator);
}

void APlayerCharacter::BeKilledBy(const AController* Killer)
{
	Super::BeKilledBy(Killer);
	check(Killer)

	if (Killer != GetPlayerController()) // 不是自杀
	{
		if (const APlayerController* KillerPlayer = Cast<APlayerController>(Killer))
		{
			if (AOnlinePlayerState* OnlinePlayerState = KillerPlayer->GetPlayerState<AOnlinePlayerState>())
			{
				OnlinePlayerState->AddScore(100);
			}
		}
	}
}

void APlayerCharacter::Aim()
{
	if (GetVelocity().Size() < 10.f)
	{
		if (HoldingComponent)
		{
			if (AGun* Gun = Cast<AGun>(HoldingComponent->GetCurrentHolding()))
			{
				UGameplayStatics::PlaySound2D(this, AimSound);
				bUseControllerRotationYaw = false;
				AnimationComponent->SetAiming(true);
			}
		}
	}
}

void APlayerCharacter::UnAim()
{
	bUseControllerRotationYaw = true;
	AnimationComponent->SetAiming(false);
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		UnAim();
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		UnAim();
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
<<<<<<< HEAD
	PlayerInputComponent->BindAxis("SwitchHolding", this->HoldingComponent, &UHoldComponent::SwitchHoldingWithAxis);
=======
	PlayerInputComponent->BindAxis("SwitchHolding", this->HoldingComponent, &UHoldingComponent::SwitchHoldingWithAxis);
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc

	PlayerInputComponent->BindAxis("MobileTurn", this, &APlayerCharacter::MobileTurn);
	PlayerInputComponent->BindAxis("MobileLookUp", this, &APlayerCharacter::MobileLookUp);

	PlayerInputComponent->BindAction("UseCurrentHolding", IE_Pressed, this->HoldingComponent,
<<<<<<< HEAD
	                                 &UHoldComponent::UseCurrentHolding);

	PlayerInputComponent->BindAction("UseCurrentHolding", IE_Released, this->HoldingComponent,
	                                 &UHoldComponent::UsedCurrentHolding);

	PlayerInputComponent->BindAction("SwitchWeaponLeft", IE_Pressed, this->HoldingComponent,
	                                 &UHoldComponent::SwitchHoldingLeft);
	PlayerInputComponent->BindAction("SwitchWeaponRight", IE_Pressed, this->HoldingComponent,
	                                 &UHoldComponent::SwitchHoldingRight);
=======
	                                 &UHoldingComponent::UseCurrentHolding);

	PlayerInputComponent->BindAction("UseCurrentHolding", IE_Released, this->HoldingComponent,
	                                 &UHoldingComponent::UsedCurrentHolding);

	PlayerInputComponent->BindAction("SwitchWeaponLeft", IE_Pressed, this->HoldingComponent,
	                                 &UHoldingComponent::SwitchHoldingLeft);
	PlayerInputComponent->BindAction("SwitchWeaponRight", IE_Pressed, this->HoldingComponent,
	                                 &UHoldingComponent::SwitchHoldingRight);
>>>>>>> 5a82f9e6a7647c355d223f9b8abdafe06ff475dc

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &APlayerCharacter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &APlayerCharacter::UnAim);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		ObtainHolding(HandClass);
		ObtainHolding(GunClass);
	}

	if (IsLocallyControlled())
	{
		BloodBarComponent->DestroyComponent();
	}

	if (const AOnlinePlayerState* OnlinePlayerState = GetState())
	{
		const FVector Color = OnlinePlayerState->GetColor();
		GetMesh()->SetVectorParameterValueOnMaterials(TEXT("BodyColor"), Color);
	}
}
