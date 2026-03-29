// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharterAnimInstance.h"
#include "Characters/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMainCharterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	if (MainCharacter)
	{
		MainCharacterMovement = MainCharacter->GetCharacterMovement();
	}
}

void UMainCharterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (MainCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MainCharacterMovement->Velocity);
		IsFalling = MainCharacterMovement->IsFalling();
		CharacterState = MainCharacter->GetCharacterState();
	}
}
