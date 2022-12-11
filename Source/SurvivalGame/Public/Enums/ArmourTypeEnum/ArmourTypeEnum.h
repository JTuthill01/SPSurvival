#pragma once

UENUM(BlueprintType)
enum class EArmourType : uint8 { EAT_Helmet UMETA(DisplayName = "Helmet"), EAT_Chest UMETA(DisplayName = "Chest"), EAT_Pants UMETA(DisplayName = "Pants"),
	EAT_Boots UMETA(DisplayName = "Boots"), EAT_Default UMETA(DisplayName = "Default") };