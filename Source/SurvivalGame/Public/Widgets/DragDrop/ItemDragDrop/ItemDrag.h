#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Enums/ContainerType/ContainerType.h"
#include "Enums/ItemTypeEnum/ItemTypeEnum.h"
#include "Enums/ArmourTypeEnum/ArmourTypeEnum.h"
#include "ItemDrag.generated.h"

UCLASS()
class SURVIVALGAME_API UItemDrag : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UItemDrag();

public:
	void SetVariables(int32 InSlotIndex, EContainerType InFromContainer, EItemType InItemType, EArmourType InArmourType);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	TObjectPtr<UUserWidget> WidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	FVector2D DragOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	EContainerType FromContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables)
	EArmourType ArmourType;
};
