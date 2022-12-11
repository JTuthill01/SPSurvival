#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Player/PlayerRefInterface.h"
#include "Enums/ArmourTypeEnum/ArmourTypeEnum.h"
#include "Enums/ContainerType/ContainerType.h"
#include "Structs/Items/Str_Items.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SURVIVALGAME_API APlayerCharacter : public ACharacter, public IPlayerRefInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

public:
	APlayerCharacter* GetPlayerRef_Implementation() override;

public:
	//Player Death
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PawnClientRestart() override;

	void OnSlotDrop(EContainerType TargetContainer, EContainerType FromContainer, EArmourType ArmourType, int32 FromIndex, int32 DroppedIndex);

	void Temp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Mapping Contexts//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InputMappings)
	TObjectPtr<class UInputMappingContext> PlayerBaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = InputMappings)
	int32 BaseMappingPriority = 0;

private:
	void ScanForInteractables();

	void PlayerSetup();

	void SetItemData();

private:
	UPROPERTY()
	TObjectPtr<UAnimInstance> PlayerAnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SK_Mesh, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Arms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InventoryComponent, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPlayerInventoryComponent> PlayerInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parser, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UJSONParser> DataParser;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Structs, meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;

private:
	TArray<FString> PathArray;

	TArray<uint8> EnumArray;

private:
	float InteractableTraceTimer;

	FTimerHandle InteractableTraceTimerHandle;
};
