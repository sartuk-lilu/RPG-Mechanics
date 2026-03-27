// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Bird.generated.h" 


UCLASS()
class RPG_API ABird : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABird();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Adding Map input for the bird
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* BirdMappingContext;
	
	// Adding Move action input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;
	
	// Adding Look action input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;
	
	UFUNCTION()
	void PlayerMovement(const FInputActionValue& Value);
	
	UFUNCTION()
	void PlayerLooking(const FInputActionValue& Value);
	
private:
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* BirdMesh;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* ViewCamera;
};

