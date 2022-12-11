#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8 { EIT_Resource UMETA(DisplayName = "Resource"), EIT_Equipable UMETA(DisplayName = "Equipable"), EIT_Armour UMETA(DisplayName = "Armour"), EIT_Consumable UMETA(DisplayName = "Consumable"),
	EIT_Buildable UMETA(DisplayName = "Buildable"), EIT_Default UMETA(DisplayName = "Default") };