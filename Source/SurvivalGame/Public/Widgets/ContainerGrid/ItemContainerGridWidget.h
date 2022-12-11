#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ContainerType/ContainerType.h"
#include "ItemContainerGridWidget.generated.h"

UCLASS()
class SURVIVALGAME_API UItemContainerGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UItemContainerGridWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

public:
	FORCEINLINE TArray<TObjectPtr<class UInventorySlotWidget>> GetSlotWidgetArray() { return SlotWidgetArray; }

public:
	UFUNCTION(BlueprintCallable)
	void SetSlotsPerRow(int32 Value) { SlotsPerRow = Value; }

	UFUNCTION(BlueprintCallable)
	void SetTotalSlotsPerRow(int32 Value) { TotalSlotsPerRow = Value; }

	UFUNCTION(BlueprintCallable)
	void SetContainerType(EContainerType NewType) { ContainerType = NewType; }

public:
	void AddSlots(int32 InAmount);

	void AddSlotToGrid(int32 Index, TObjectPtr<class UInventorySlotWidget> SlotPtr);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUniformGridPanel> Grid;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Widgets, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> SlotsSubclass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GridVariables, meta = (AllowPrivateAccess = "true"))
	int32 SlotsPerRow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = GridVariables, meta = (AllowPrivateAccess = "true"))
	int32 TotalSlotsPerRow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enums, meta = (AllowPrivateAccess = "true"))
	EContainerType ContainerType;

private:
	UPROPERTY()
	TObjectPtr<class UInventorySlotWidget> SlotWidget;

	UPROPERTY()
	TArray<TObjectPtr<class UInventorySlotWidget>> SlotWidgetArray;
};
