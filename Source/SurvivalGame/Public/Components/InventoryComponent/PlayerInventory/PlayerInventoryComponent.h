#pragma once

#include "CoreMinimal.h"
#include "Components/InventoryComponent/ItemsContainer.h"
#include "PlayerInventoryComponent.generated.h"

UCLASS()
class SURVIVALGAME_API UPlayerInventoryComponent : public UItemsContainer
{
	GENERATED_BODY()
	
public:
	UPlayerInventoryComponent();

public:
	virtual void AddItems(FItemData Item, bool& bWasSuccessful) override;

	virtual void TransferItem(TObjectPtr<UItemsContainer> ToComponent, int32 ToSpecificIndex, int32 TransferIndex) override;

	virtual void HandleSlotDrop(TObjectPtr<UItemsContainer> FromComponent, int32 FromIndex, int32 DroppedIndex) override;

	virtual void AddItemToIndex(FItemData Item, int32 SpecificIndex, int32 FromIndex, bool& bWasSuccessful) override;

protected:
	virtual void BeginPlay() override;
};
