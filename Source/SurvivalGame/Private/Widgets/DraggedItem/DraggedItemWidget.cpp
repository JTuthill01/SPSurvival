#include "Widgets/DraggedItem/DraggedItemWidget.h"
#include "Components/Border.h"
#include "Engine/Texture2D.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UDraggedItemWidget::UDraggedItemWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDraggedItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ItemIcon->SetBrushFromTexture(ImageIcon);

	ItemIcon->SetVisibility(ESlateVisibility::Visible);

	SetItemType();

	QuantityText->SetVisibility(ESlateVisibility::Visible);
}

void UDraggedItemWidget::SetWidgetProperties(TObjectPtr<class UTexture2D> InImageIcon, FText InTopText, EItemType InItemType, FText InQuantity, bool bInUsesAmmo,
	int32 InCurrentAmmo, int32 InMaxAmmo, int32 InCurrentHP, int32 InMaxHP)
{
	ImageIcon = InImageIcon;

	TopText->SetText(InTopText);

	ItemType = InItemType;

	QuantityText->SetText(InQuantity);

	Quantity = InQuantity;

	bUsesAmmo = bInUsesAmmo;

	CurrentAmmo = InCurrentAmmo;

	MaxAmmo = InMaxAmmo;

	CurrentHP = InCurrentHP;

	MaxHP = InMaxHP;
}

#if WITH_EDITOR
#define LOCTEXT_NAMESPACE "UMG"
void UDraggedItemWidget::SetItemType()
{
	switch (ItemType)
	{
	case EItemType::EIT_Resource:

		Quantity = FText::Format(LOCTEXT("Quantity", "x{Quantity}"), Quantity);

		QuantityText->SetText(Quantity);

		QuantityText->SetVisibility(ESlateVisibility::Visible);

		break;
	
	case EItemType::EIT_Equipable:
		break;

	case EItemType::EIT_Armour:
		break;

	case EItemType::EIT_Consumable:
		break;

	case EItemType::EIT_Buildable:
		break;

	case EItemType::EIT_Default:
		break;

	default:
		break;
	}
}

void UDraggedItemWidget::UpdateSlot(FItemData ItemInfo)
{
	FText P = FText::AsNumber(ItemInfo.ItemQuanity);
	FText Q = FText::Format(LOCTEXT("Quantity", "x{Quantity}"), P);

	QuantityText->SetText(Q);
	QuantityText->SetVisibility(ESlateVisibility::Visible);
}
#undef LOCTEXT_NAMESPACE
#endif