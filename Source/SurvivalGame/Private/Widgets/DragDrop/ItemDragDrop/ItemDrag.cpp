#include "Widgets/DragDrop/ItemDragDrop/ItemDrag.h"

UItemDrag::UItemDrag() : DragOffset(FVector2D(0)), SlotIndex(0), FromContainer(EContainerType::ECT_Default), ItemType(EItemType::EIT_Default), ArmourType(EArmourType::EAT_Default)
{
}

void UItemDrag::SetVariables(int32 InSlotIndex, EContainerType InFromContainer, EItemType InItemType, EArmourType InArmourType)
{
	SlotIndex = InSlotIndex;

	FromContainer = InFromContainer;

	ItemType = InItemType;

	ArmourType = InArmourType;
}

