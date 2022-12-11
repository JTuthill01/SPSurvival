#include "Widgets/Slots/InventorySlot/InventorySlotWidget.h"
#include "Character/Player/PlayerCharacter.h"
#include "Interfaces/Player/PlayerRefInterface.h"
#include "Widgets/DraggedItem/DraggedItemWidget.h"
#include "Widgets/DragDrop/ItemDragDrop/ItemDrag.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

UInventorySlotWidget::UInventorySlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), FromContainer(EContainerType::ECT_Default), ItemIndex(0), bHasItemInSlot(false)
{
}

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemIcon->SetVisibility(ESlateVisibility::Hidden);

	TopText->SetVisibility(ESlateVisibility::Hidden);

	BottomText->SetVisibility(ESlateVisibility::Hidden);

	QuanityText->SetVisibility(ESlateVisibility::Hidden);

	ItemHP->SetVisibility(ESlateVisibility::Hidden);
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);

		return Reply;
	}

	return FReply::Unhandled();
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	TObjectPtr<UItemDrag> IDrag = Cast<UItemDrag>(InOperation);

	TObjectPtr<APlayerCharacter> PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(PlayerRef) && IsValid(IDrag))
	{
		PlayerRef->OnSlotDrop(FromContainer, IDrag->FromContainer, IDrag->ArmourType, IDrag->SlotIndex, ItemIndex);

		return true;
	}

	return false;
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (bHasItemInSlot)
	{
		DraggedItemWidget = CreateWidget<UDraggedItemWidget>(GetWorld(), DraggedWidgetSubclass);

		FText Damage = FText::AsNumber(ItemData.ItemDamage);
		FText Quantity = FText::AsNumber(ItemData.ItemQuanity);

		if (IsValid(DraggedItemWidget))
		{
			DraggedItemWidget->SetWidgetProperties(DragData.ItemIcon, Damage, DragData.ItemType, Quantity, DragData.bUsesAmmo, DragData.CurrentAmmo, DragData.MaxAmmo,
				DragData.ItemCurrentHP, DragData.ItemMaxHP);

			DragDrop(InGeometry, InMouseEvent, OutOperation);

			ItemDrag->SetVariables(ItemIndex, FromContainer, ItemData.ItemType, ItemData.ArmourType);
		}
	}
}

void UInventorySlotWidget::DragDrop(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	ItemDrag = NewObject<UItemDrag>();

	ItemDrag->WidgetReference = this;
	ItemDrag->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	ItemDrag->DefaultDragVisual = DraggedItemWidget;
	ItemDrag->Pivot = EDragPivot::MouseDown;

	OutOperation = ItemDrag;
}

#if WITH_EDITOR
#define LOCTEXT_NAMESPACE "UMG"
void UInventorySlotWidget::UpdateSlot(FItemData ItemInfo)
{
	bHasItemInSlot = true;

	ItemIcon->SetBrushFromTexture(ItemInfo.ItemIcon);
	ItemIcon->SetVisibility(ESlateVisibility::Visible);

	DragIcon = ItemInfo.ItemIcon;
	DragData = ItemInfo;

	FText P = FText::AsNumber(ItemInfo.ItemQuanity);
	FText Q = FText::Format(LOCTEXT("Quanity", "x{Quanity}"), P);

	QuanityText->SetText(Q);
	QuanityText->SetVisibility(ESlateVisibility::Visible);
}
#undef LOCTEXT_NAMESPACE
#endif