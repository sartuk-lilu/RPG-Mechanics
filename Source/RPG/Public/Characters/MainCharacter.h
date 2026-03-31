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
class AWeapon;

// Structures
struct FInputActionValue;

UCLASS()
class RPG_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	
	
	/*------------------------------------------*/
	/* Getters and Setters */
	/*------------------------------------------*/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE void SetOverlappingItem(AItem* Item) {OverlappingItem = Item; }
	
	FORCEINLINE ECharacterState GetCharacterState() const {return CharacterState; }

protected:
	virtual void BeginPlay() override;
		
	/*------------------------------------------*/
	/* MAPPING INPUT FOR THE MAIN CHARACTER */
	/*------------------------------------------*/
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MainCharacterInputMapping;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
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
	// IA_Take
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* TakeItemAction;
	// IA_Attack
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* AttackAction;
	// IA_EquipWeapon
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* EquipWeaponAction;
	
	
	/*------------------------------------------*/
	/* INPUT ACTION FUNCTIONS FOR THE MAIN CHARACTER */
	/*------------------------------------------*/
	void Movement(const FInputActionValue& Value);

	void MouseLooking(const FInputActionValue& Value);

	void MouseWheel(const FInputActionValue& Value);

	void TakeItem(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);
	
	void EquipWeapon(const FInputActionValue& Value);
	
	/*------------------------------------------*/
	/* Animation Montage */
	/*------------------------------------------*/
	void PlayAttackMontage();
	void PlayEquipMontage();
	
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	
	UFUNCTION(BlueprintCallable)
	void Disarm();
	
	UFUNCTION(BlueprintCallable)
	void Arm();
		
	bool CanAttack() const;
	
	UFUNCTION(BlueprintCallable)
	void EquipFinished();
	
	UFUNCTION(BlueprintCallable)
	void SetWeaponCollision(ECollisionEnabled::Type CollisionEnabled);

	
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
	
	UPROPERTY(VisibleAnywhere, Category="Weapon")
	AWeapon* EquippedWeapon;
	
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	UAnimMontage* AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	UAnimMontage* EquipMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Montages", meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState = ECharacterState::Unarmed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Montages", meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::Unoccupied;
};
