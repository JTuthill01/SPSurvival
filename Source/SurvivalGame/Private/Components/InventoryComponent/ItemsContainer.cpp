#include "Components/InventoryComponent/ItemsContainer.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UItemsContainer::UItemsContainer() : ContainerType(EContainerType::ECT_PlayerInventory)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UItemsContainer::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void UItemsContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UItemsContainer::FindEmptySlot(bool& bIsSuccessful, int32& EmptyIndex)
{
	for (int32 i = 0; i < ItemsArray.Num(); ++i)
	{
		if (ItemsArray[i].ItemID == NULL)
		{
			EmptyIndex = i;

			bIsSuccessful = true;

			return;
		}

		else 
			continue;
	}
}

void UItemsContainer::AddItems(FItemData Item, bool& bWasSuccessful)
{
	int32 LocalIndex;

	FindEmptySlot(bWasSuccessful, LocalIndex);

	if (bWasSuccessful)
	{
		ItemsArray.Insert(Item, LocalIndex);

		UpdateUI(LocalIndex, Item);
	}
}

void UItemsContainer::AddItemToIndex(FItemData Item, int32 SpecificIndex, int32 FromIndex, bool& bWasSuccessful)
{
	const bool bIsSlotEmpty = IsSlotEmpty(SpecificIndex);

	if (bIsSlotEmpty)
	{
		Item = ItemsArray[SpecificIndex];

		bWasSuccessful = true;
	}

	else
		bWasSuccessful = false;
}

void UItemsContainer::UpdateUI(int32 Index, FItemData ItemInfo, bool bShouldResetSlot)
{
	if (!bShouldResetSlot)
	{
		switch (ContainerType)
		{
		case EContainerType::ECT_PlayerInventory:

			if (!IsValid(PC))
				break;

			PC->UpdateItemSlot(ContainerType, Index, ItemInfo);

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
}

void UItemsContainer::TransferItem(TObjectPtr<UItemsContainer> ToComponent, int32 ToSpecificIndex, int32 TransferIndex)
{
	bool bIsSuccessful;

	if (IsValid(ToComponent))
	{
		FItemData ItemToTransfer = GetItemIndex(TransferIndex);

		ToComponent->AddItemToIndex(ItemToTransfer, ToSpecificIndex, TransferIndex, bIsSuccessful);
	}
}

void UItemsContainer::OnSlotDrop(TObjectPtr<UItemsContainer> FromContainer, int32 FromIndex, int32 DroppedIndex)
{
	HandleSlotDrop(FromContainer, FromIndex, DroppedIndex);
}

FItemData UItemsContainer::GetItemIndex(int32 CurrentIndex)
{
	if (ItemsArray.IsValidIndex(CurrentIndex))
		return ItemsArray[CurrentIndex];
	
	return FItemData();
}

bool UItemsContainer::IsSlotEmpty(int32 Index)
{
	if (ItemsArray[Index].ItemID == NULL)
		return true;

	return false;
}

void UItemsContainer::HandleSlotDrop(TObjectPtr<UItemsContainer> FromComponent, int32 FromIndex, int32 DroppedIndex) { /* This Function Was Left Intentionally Blank **/ }