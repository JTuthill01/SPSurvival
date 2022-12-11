#pragma once

UENUM(BlueprintType)
enum class EItemRarity : uint8 { EIR_Common UMETA(DisplayName = "Common"), EIR_Uncommon UMETA(DisplayName = "Uncommon"), EIR_Rare UMETA(DisplayName = "Rare"), EIR_Epic UMETA(DisplayName = "Epic"), 
	EIR_Legendary UMETA(DisplayName = "Legendary"), EIR_Default UMETA(DisplayName = "Default") };