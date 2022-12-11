// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/Items/Str_Items.h"
#include "Enums/ContainerType/ContainerType.h"
#include "ItemsContainer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UItemsContainer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemsContainer();

public:
	FORCEINLINE EContainerType GetContainerType() { return ContainerType; }

	FORCEINLINE void SetContainerType(EContainerType NewType) { ContainerType = NewType; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void FindEmptySlot(bool& bIsSuccessful, int32& EmptyIndex);

	virtual void AddItems(FItemData Item, bool& bWasSuccessful);

	virtual void AddItemToIndex(FItemData Item, int32 SpecificIndex, int32 FromIndex, bool& bWasSuccessful);

	virtual void UpdateUI(int32 Index, FItemData ItemInfo, bool bShouldResetSlot = false);

	virtual void TransferItem(TObjectPtr<UItemsContainer> ToComponent, int32 ToSpecificIndex, int32 TransferIndex);

	virtual void HandleSlotDrop(TObjectPtr<UItemsContainer> FromComponent, int32 FromIndex, int32 DroppedIndex);

	virtual void OnSlotDrop(TObjectPtr<UItemsContainer> FromContainer, int32 FromIndex, int32 DroppedIndex);

	virtual FItemData GetItemIndex(int32 CurrentIndex);

	virtual bool IsSlotEmpty(int32 Index);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FItemData> ItemsArray;

protected:
	UPROPERTY()
	TObjectPtr<class APlayerCharacterController> PC;

protected:
	EContainerType ContainerType;
};
