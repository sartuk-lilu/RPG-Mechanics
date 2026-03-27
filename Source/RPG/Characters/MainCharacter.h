// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/CharacterStates.h"
#include "MainCharacter.generated.h"

// Forward Declarations
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UGroomComponent;
class AItem;
class UAnimMontage;

// Structures
struct FInputActionValue;

UCLASS()
class RPG_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	
	/*------------------------------------------*/
	/* Getters and Setters */
	/*------------------------------------------*/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE void SetOverlappingItem(AItem* Item) {OverlappingItem = Item; }
	
	FORCEINLINE ECharacterState GetCharacterState() const {return CharacterState; }
	/*------------------------------------------*/
protected:
	virtual void BeginPlay() override;
	
	
	
	/*------------------------------------------*/
	/* MAPPING INPUT FOR THE MAIN CHARACTER */
	/*------------------------------------------*/
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MainCharacterInputMapping;
	/*------------------------------------------*/
		
	
	
	/*------------------------------------------*/
	/* ALL INPUT ACTIONS FOR THE MAIN CHARACTER */
	/*------------------------------------------*/
	// IA_Jump
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;
	// IA_Movement
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	// IA_MouseLook
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;
	// IA_MouseWheelZoom
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseWheelAction;
	// IA_Equip
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* EquipAction;
	// IA_Attack
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* AttackAction;
	/*------------------------------------------*/
	
	
	
	/*------------------------------------------*/
	/* INPUT ACTION FUNCTIONS FOR THE MAIN CHARACTER */
	/*------------------------------------------*/
	// Movement
	void CharacterMovement(const FInputActionValue& Value);

	// MouseLooking
	void CharacterMouseLooking(const FInputActionValue& Value);
	
	// Mouse Zooming
	void CharacterMouseWheel(const FInputActionValue& Value);
	
	// Equip an Item on the main character
	void CharacterEquip(const FInputActionValue& Value);
	
	//Attack
	void CharacterAttack(const FInputActionValue& Value);
	/*------------------------------------------*/
	
	
	
private:
		
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/* Grooming components */
	UPROPERTY(EditAnywhere, Category="Groom")
	UGroomComponent* Hair;
	
	UPROPERTY(EditAnywhere, Category="Groom")
	UGroomComponent* Eyebrows;
	
	/* Mouse Wheel Variables */	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MouseWheelZoom", meta = (AllowPrivateAccess = "true"))
	float ArmLengthScale = 45.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MouseWheelZoom", meta = (AllowPrivateAccess = "true"))
	float MinArmLength = 45.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MouseWheelZoom", meta = (AllowPrivateAccess = "true"))
	float MaxArmLength = 450.f;
	
	UPROPERTY(VisibleAnywhere, Category="MouseWheelZoom")
	float WishBoomArmLength = 300.f;
	
	UPROPERTY(VisibleAnywhere, Category="MouseWheelZoom")
	bool IsCameraZooming = false;
	
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;
	
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	UAnimMontage* AttackMontage;
	
	ECharacterState CharacterState = ECharacterState::ECS_Unarmed;
};
