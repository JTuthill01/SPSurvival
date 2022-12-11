#include "Components/InventoryComponent/PlayerInventory/PlayerInventoryComponent.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"

UPlayerInventoryComponent::UPlayerInventoryComponent() = default;

void UPlayerInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerInventoryComponent::AddItems(FItemData Item, bool& bWasSuccessful)
{
	Super::AddItems(Item, bWasSuccessful);
}

void UPlayerInventoryComponent::TransferItem(TObjectPtr<UItemsContainer> ToComponent, int32 ToSpecificIndex, int32 TransferIndex)
{
	Super::TransferItem(ToComponent, ToSpecificIndex, TransferIndex);
}

void UPlayerInventoryComponent::HandleSlotDrop(TObjectPtr<UItemsContainer> FromComponent, int32 FromIndex, int32 DroppedIndex)
{
	Super::HandleSlotDrop(FromComponent, FromIndex, DroppedIndex);

	switch (ContainerType)
	{
	case EContainerType::ECT_PlayerInventory:

		TransferItem(this, DroppedIndex, FromIndex);

		break;

	case EContainerType::ECT_PlayerHotbar:
		break;

	case EContainerType::ECT_PlayerStorage:
		break;

	case EContainerType::ECT_PlayerArmour:
		break;

	case EContainerType::ECT_Default:
		break;

	default:
		break;
	}
}

void UPlayerInventoryComponent::AddItemToIndex(FItemData Item, int32 SpecificIndex, int32 FromIndex, bool& bWasSuccessful)
{
	Super::AddItemToIndex(Item, SpecificIndex, FromIndex, bWasSuccessful);

	if (!IsValid(PC))
		PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	else if (IsValid(PC))
		PC->UpdateItemSlot(ContainerType, SpecificIndex, GetItemIndex(SpecificIndex));

	else
		return;
}
