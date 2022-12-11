#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Items/Str_Items.h"
#include "Enums/ContainerType/ContainerType.h"
#include "Enums/ItemTypeEnum/ItemTypeEnum.h"
#include "Enums/ArmourTypeEnum/ArmourTypeEnum.h"
#include "InventorySlotWidget.generated.h"

UCLASS()
class SURVIVALGAME_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventorySlotWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetItemIndex(int32 Value) { ItemIndex = Value; }

	FORCEINLINE int32 GetItemIndex() { return ItemIndex; }

public:
	virtual void NativeConstruct() override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	void UpdateSlot(FItemData ItemInfo);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TopText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> BottomText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> QuanityText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ItemHP;

private:
	void DragDrop(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widgets, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> DraggedWidgetSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widgets, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDragDropOperation> ItemDragSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Structs, meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	EContainerType FromContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Variables, meta = (AllowPrivateAccess = "true"))
	int32 ItemIndex;

private:
	UPROPERTY()
	TObjectPtr<class UDraggedItemWidget> DraggedItemWidget;

	UPROPERTY()
	TObjectPtr<class UItemDrag> ItemDrag;

	UPROPERTY()
	TObjectPtr<UTexture2D> DragIcon;

private:
	bool bHasItemInSlot;

	FItemData DragData;
};
