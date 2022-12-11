#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

UCLASS()
class SURVIVALGAME_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

public:
	TObjectPtr<class UInventoryWidget> GetInventoryRef() { return InventoryRef; }

	void SetInventoryVisibility(bool bIsVisible);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InventoryWidget, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInventoryWidget> InventoryRef; 
};
