#include "Character/Player/PlayerCharacter.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Components/InventoryComponent/PlayerInventory/PlayerInventoryComponent.h"
#include "JSONParser/JSONParser.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : InteractableTraceTimer(0.25F)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);
	Arms->SetCastShadow(false);

	PlayerInventoryComponent = CreateDefaultSubobject<UPlayerInventoryComponent>(L"PlayerInventoryComponent");

	DataParser = CreateDefaultSubobject<UJSONParser>(L"DataParser");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerSetup();
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearAllTimersForObject(this);
}

void APlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController.
	if (APlayerCharacterController* PC = Cast<APlayerCharacterController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values out prioritize lower values.
			Subsystem->AddMappingContext(PlayerBaseMappingContext, BaseMappingPriority);
		}
	}
}

void APlayerCharacter::Temp()
{
	bool bTempBool;

	PlayerInventoryComponent->AddItems(ItemData, bTempBool);
}

void APlayerCharacter::ScanForInteractables()
{
	
}

void APlayerCharacter::PlayerSetup()
{
	if (IsValid(Arms))
		PlayerAnimInstance = Arms->GetAnimInstance();

	if (IsValid(DataParser))
	{
		DataParser->SetObjectData("Wood");

		DataParser->Parser(ItemData, PathArray, EnumArray);

		SetItemData();
	}

	GetWorldTimerManager().SetTimer(InteractableTraceTimerHandle, this, &APlayerCharacter::ScanForInteractables, InteractableTraceTimer, true);
}

void APlayerCharacter::SetItemData()
{
	ItemData.ItemIcon = LoadObject<class UTexture2D>(this, *PathArray[0]);

	ItemData.ItemRarity = static_cast<EItemRarity>(EnumArray[0]);
	ItemData.ItemType = static_cast<EItemType>(EnumArray[1]);
	ItemData.ArmourType = static_cast<EArmourType>(EnumArray[2]);
}

void APlayerCharacter::OnSlotDrop(EContainerType TargetContainer, EContainerType FromContainer, EArmourType ArmourType, int32 FromIndex, int32 DroppedIndex)
{
	//TargetContainer = PlayerInventoryComponent->GetContainerType();

	PlayerInventoryComponent->OnSlotDrop(PlayerInventoryComponent, FromIndex, DroppedIndex);
}

APlayerCharacter* APlayerCharacter::GetPlayerRef_Implementation() { return this; }

