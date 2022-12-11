#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class SURVIVALGAME_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

public:
	TObjectPtr<class UItemContainerGridWidget> GetContainerGrid() { return ContainerGrid; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Grid, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UItemContainerGridWidget> ContainerGrid;
};
