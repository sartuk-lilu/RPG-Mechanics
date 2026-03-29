// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GroomComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	// Create a grooming component Hair
	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = TEXT("head");
	
	// Create a grooming component Eyebrows
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = TEXT("head");
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MainCharacterInputMapping, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::CharacterMovement);
		
		// Looking
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMainCharacter::CharacterMouseLooking);
		
		// MouseWheel Zooming
		EnhancedInputComponent->BindAction(MouseWheelAction, ETriggerEvent::Triggered, this, &AMainCharacter::CharacterMouseWheel);
		
		// Equip
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AMainCharacter::CharacterEquip);
		
		//Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMainCharacter::CharacterAttack);
	}
}
void AMainCharacter::CharacterMovement(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(RightDirection, MovementVector.X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
}

void AMainCharacter::CharacterMouseLooking(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMainCharacter::CharacterMouseWheel(const FInputActionValue& Value)
{
	if (GetCameraBoom())
	{
		//Wish Length = Input Value * Scaler + Current Boom Length if not out of limits
		WishBoomArmLength = FMath::Clamp<float>(
			Value.Get<float>() * ArmLengthScale + GetCameraBoom()->TargetArmLength, 
			MinArmLength, 
			MaxArmLength);
		IsCameraZooming = true;
	}
}

void AMainCharacter::CharacterEquip(const FInputActionValue& Value)
{
	if (AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem))
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		MoveIgnoreActorAdd(OverlappingWeapon);
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	}
}

void AMainCharacter::PlayAttackMontage()
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (AttackMontage)
		{
			AnimInstance->Montage_Play(AttackMontage);
			const int32 Selection = FMath::RandRange(0,1);
			FName SectionName = FName();
			switch (Selection)
			{
			case 0:
				SectionName = FName("Attack1");
				break;
			case 1:
				SectionName = FName("Attack2");
				break;
			default:
				break;
			}
			AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
		}
	}
}

void AMainCharacter::CharacterAttack(const FInputActionValue& Value)
{
	if (CharacterActionState == EActionState::EAS_Unoccupied)
	{
		PlayAttackMontage();
		CharacterActionState = EActionState::EAS_Attacking;
	}
	
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//if Wished Boom Length different from the Current
	if (GetCameraBoom() && IsCameraZooming)
	{
		float& Current = GetCameraBoom()->TargetArmLength;
		//slowly changing camera boom length
		GetCameraBoom()->TargetArmLength = FMath::FInterpTo(
			Current, 
			WishBoomArmLength, 
			DeltaTime, 
			1.f);
		if (FMath::IsNearlyEqual(Current, WishBoomArmLength, 0.1f))
		{
			Current = WishBoomArmLength;
			IsCameraZooming = false;
		}
	}
}