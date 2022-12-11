#pragma once

#include "Engine/DataTable.h"
#include "Items/ItemBase/ItemBase.h"
#include "Enums/ItemRarityEnum/ItemRarityEnum.h"
#include "Enums/ItemTypeEnum/ItemTypeEnum.h"
#include "Enums/ArmourTypeEnum/ArmourTypeEnum.h"
#include "Str_Items.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUsesAmmo = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemQuanity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemCurrentHP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemMaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StackSize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmo = MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UTexture2D> ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItemBase> ItemBaseRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity ItemRarity = EItemRarity::EIR_Default; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType = EItemType::EIT_Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EArmourType ArmourType = EArmourType::EAT_Default;
};