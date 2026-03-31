// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;

UCLASS()
class RPG_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	AWeapon();
	
	void AttachMeshToSocket(USceneComponent* InParent, FName InSocketName);
	void Equip(USceneComponent* InParent, FName InSocketName);
	
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
	
protected:
	virtual void BeginPlay() override;
	
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherOverlappedComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult ) override;

	virtual void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex ) override;
	
	UFUNCTION()
	void OnBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherOverlappedComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult );
	
private:
	UPROPERTY(EditAnywhere, Category = "Weapon Property")
	USoundBase* EquipSound;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	UBoxComponent* WeaponCollisionBox;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	USceneComponent* BoxTraceStart;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	USceneComponent* BoxTraceEnd;
	
	UPROPERTY(EditAnywhere, Category = "Weapon Property")
	FVector BoxTraceCollision = FVector(5.0f, 5.0f, 5.0f);
};
