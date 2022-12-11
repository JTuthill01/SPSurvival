#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Items/Str_Items.h"
#include "Enums/ItemTypeEnum/ItemTypeEnum.h"
#include "DraggedItemWidget.generated.h"

UCLASS()
class SURVIVALGAME_API UDraggedItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDraggedItemWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativeConstruct() override;

public:
	void UpdateSlot(FItemData ItemInfo);

	void SetWidgetProperties(TObjectPtr<class UTexture2D> InImageIcon, FText InTopText, EItemType InItemType, FText InQuantity, bool bInUsesAmmo, int32 InCurrentAmmo, int32 InMaxAmmo, 
			int32 InCurrentHP, int32 InMaxHP);

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TopText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> BottomText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> QuantityText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBorder> ItemIcon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ItemHP;

private:
	void SetItemType();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Images, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTexture2D> ImageIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Structs, meta = (AllowPrivateAccess = "true"))
	FItemData Info;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Enums, meta = (AllowPrivateAccess = "true"))
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Text, meta = (AllowPrivateAccess = "true"))
	FText Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Ints, meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Ints, meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Ints, meta = (AllowPrivateAccess = "true"))
	int32 CurrentHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Ints, meta = (AllowPrivateAccess = "true"))
	int32 MaxHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Bools, meta = (AllowPrivateAccess = "true"))
	bool bUsesAmmo;
};
