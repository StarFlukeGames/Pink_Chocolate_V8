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

void UNinjaInputHandler_Customization::HandleTriggeredEvent_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value,
	const UInputAction* InputAction,
	float ElapsedTime) const
{
	if (!Manager) return;

	// Filter digital false/release states
	if (!Value.Get<bool>()) return;

	// Retrieve controller reference directly from Manager
	const AController* Controller = Manager->GetController();
	if (!Controller) return;

	APawn* ControlledPawn = Controller->GetPawn();
	if (!ControlledPawn) return;

	APlayerState* PS = ControlledPawn->GetPlayerState();
	if (!PS) return;

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PS);
	if (!ASC) return;
	
	FGameplayTagContainer InputTags;

	if (InputAction)
	{
		if (const IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(InputAction))
		{
			TagInterface->GetOwnedGameplayTags(InputTags);
		}
	}

	// Fallback: Check if this Handler object itself has tags attached
	if (InputTags.IsEmpty())
	{
		if (const IGameplayTagAssetInterface* HandlerTagInterface = Cast<IGameplayTagAssetInterface>(this))
		{
			HandlerTagInterface->GetOwnedGameplayTags(InputTags);
		}
	}
	
	for (const FGameplayTag& Tag : InputTags)
	{
		FGameplayEventData Payload;
		Payload.EventTag = Tag;
		Payload.Instigator = ControlledPawn;
		Payload.Target = PS;

		ASC->HandleGameplayEvent(Tag, &Payload); //
	}
}
