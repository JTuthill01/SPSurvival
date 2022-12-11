#include "Widgets/ContainerGrid/ItemContainerGridWidget.h"
#include "Widgets/Slots/InventorySlot/InventorySlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/UniformGridSlot.h"

UItemContainerGridWidget::UItemContainerGridWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), SlotsPerRow(5), TotalSlotsPerRow(30)
{
}

void UItemContainerGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AddSlots(TotalSlotsPerRow);
}

void UItemContainerGridWidget::AddSlots(int32 InAmount)
{
	for (int32 i = 0; i < InAmount; ++i)
	{
		SlotWidget = CreateWidget<UInventorySlotWidget>(this, SlotsSubclass);

		if (!IsValid(SlotWidget))
			continue;

		SlotWidget->SetItemIndex(i);

		SlotWidgetArray.Emplace(SlotWidget);

		AddSlotToGrid(SlotWidgetArray[i]->GetItemIndex(), SlotWidget);
	}
}

void UItemContainerGridWidget::AddSlotToGrid(int32 Index, TObjectPtr<class UInventorySlotWidget> SlotPtr)
{
	TObjectPtr<UUniformGridSlot> UniformGrid = Grid->AddChildToUniformGrid(SlotPtr);

	double RemainderDouble;

	double IndexDouble = static_cast<double>(Index);
	double SlotsPerRowDouble = static_cast<double>(SlotsPerRow);

	UKismetMathLibrary::FMod(IndexDouble, SlotsPerRowDouble, RemainderDouble);

	double DivisionDouble = IndexDouble / SlotsPerRowDouble;

	int32 Row = UKismetMathLibrary::FTrunc(DivisionDouble);
	int32 Column = UKismetMathLibrary::FTrunc(RemainderDouble);
	
	UniformGrid->SetRow(Row);
	UniformGrid->SetColumn(Column);
}
