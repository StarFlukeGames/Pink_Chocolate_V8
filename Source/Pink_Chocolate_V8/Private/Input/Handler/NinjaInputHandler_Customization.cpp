// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "Input/Handler/NinjaInputHandler_Customization.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/NinjaInputManagerComponent.h"
#include "GameFramework/PlayerState.h"

UNinjaInputHandler_Customization::UNinjaInputHandler_Customization()
{
	// Restrict this class to stateless execution. Zero runtime member allocations.
}

void UNinjaInputHandler_Customization::HandleInput_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionInstance& ActionInstance,
	const ETriggerEvent TriggerEvent) const
{
	if (!Manager) return;

	// Filter digital trigger state (only execute on Pressed/Triggered events)
	bool bIsPressed = ActionInstance.GetValue().Get<bool>();
	if (!bIsPressed) return;

	AController* Controller = Manager->GetController();
	if (!Controller) return;

	APawn* ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return;

	APlayerState* PS = ControlledPawn->GetPlayerState();
	if (!PS) return;

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PS);
	if (!ASC) return;

	// Fetch tags via GetInputTags() on the handler instance
	
	FGameplayTagContainer InputTags;
	if (const UInputAction* SourceAction = ActionInstance.GetSourceAction())
	{
		if (const IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(SourceAction))
		{
			TagInterface->GetOwnedGameplayTags(InputTags);
		}
	}

	// Marshal the mapped tags to the active PlayerState's ASC as Gameplay Events.
	for (const FGameplayTag& Tag : InputTags)
	{
		FGameplayEventData Payload;
		Payload.EventTag = Tag;
		Payload.Instigator = ControlledPawn;
		Payload.Target = PS;

		ASC->HandleGameplayEvent(Tag, &Payload);
	}
}