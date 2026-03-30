#pragma once


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
	EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	Unoccupied UMETA(DisplayName = "Unoccupied"),
	Attacking UMETA(DisplayName = "Attacking"),
	Equipping UMETA(DisplayName = "Equipping"),
};