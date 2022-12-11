#include "Widgets/MainWidget/MainWidget.h"
#include "Widgets/InventoryWidget/InventoryWidget.h"

UMainWidget::UMainWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainWidget::SetInventoryVisibility(bool bIsVisible)
{
	if (bIsVisible)
		InventoryRef->SetVisibility(ESlateVisibility::Visible);

	else
		InventoryRef->SetVisibility(ESlateVisibility::Hidden);
}
