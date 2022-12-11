#include "Character/Controller/PlayerCharacterController.h"
#include "Character/Player/PlayerCharacter.h"
#include "Interfaces/Player/PlayerRefInterface.h"
#include "Widgets/MainWidget/MainWidget.h"
#include "Widgets/InventoryWidget/InventoryWidget.h"
#include "Widgets/ContainerGrid/ItemContainerGridWidget.h"
#include "Widgets/Slots/InventorySlot/InventorySlotWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacterController::APlayerCharacterController() : bIsInventoryShown(false)
{
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	Setup();
}

void APlayerCharacterController::Setup()
{
	PlayerRef = IPlayerRefInterface::Execute_GetPlayerRef(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(PlayerRef))
	{
		MainHUDWidget = CreateWidget<UMainWidget>(GetWorld(), HUDWidget);

		if (IsValid(MainHUDWidget))
			MainHUDWidget->AddToViewport();

		else
			return;
	}

	else
		return;
}

void APlayerCharacterController::UpdateItemSlot(EContainerType Type, int32 Index, FItemData ItemInfo)
{
	TArray<TObjectPtr<UInventorySlotWidget>> SlotArray = MainHUDWidget->GetInventoryRef()->GetContainerGrid()->GetSlotWidgetArray();

	if (SlotArray.IsValidIndex(Index))
		SlotArray[Index]->UpdateSlot(ItemInfo);
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (TObjectPtr<UEnhancedInputComponent> PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacterController::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacterController::StopJump);
		}

		if (MovementAction)
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);

		if (LookAction)
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);

		if (InteractAction)
			PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Interact);

		if (InventoryAction)
			PlayerEnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &APlayerCharacterController::ShowInventory);

		if (CloseWidgetAction)
			PlayerEnhancedInputComponent->BindAction(CloseWidgetAction, ETriggerEvent::Started, this, &APlayerCharacterController::CloseWidget);

		if (TestAction)
			PlayerEnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Started, this, &APlayerCharacterController::Test);
	}
}

void APlayerCharacterController::Move(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0.F)
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), Value[1]);
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Value[0]);
	}
}

void APlayerCharacterController::Look(const FInputActionValue& Value)
{
	AddPitchInput(Value[1] * -1);
	AddYawInput(Value[0]);
}


void APlayerCharacterController::Interact()
{
}

void APlayerCharacterController::ShowInventory()
{
	FInputModeGameAndUI Mode;

	if (IsValid(MainHUDWidget))
	{
		if (!bIsInventoryShown)
		{
			MainHUDWidget->SetInventoryVisibility(true);

			bShowMouseCursor = true;

			SetIgnoreLookInput(true);

			Mode.SetHideCursorDuringCapture(false);

			SetInputMode(Mode);

			bIsInventoryShown = true;
		}
	}
}

void APlayerCharacterController::CloseWidget()
{
	if (IsValid(MainHUDWidget))
	{
		if (bIsInventoryShown)
		{
			MainHUDWidget->SetInventoryVisibility(false);

			FInputModeGameOnly InputMode;

			ResetIgnoreLookInput();

			SetInputMode(InputMode);

			InputMode.SetConsumeCaptureMouseDown(true);

			bShowMouseCursor = false;

			bIsInventoryShown = false;
		}
	}
}

void APlayerCharacterController::Test()
{
	PlayerRef->Temp();
}

void APlayerCharacterController::Jump() { GetCharacter()->Jump(); }

void APlayerCharacterController::StopJump() { GetCharacter()->StopJumping(); }


