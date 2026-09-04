// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "Input/Handler/NinjaInputHandler_Customization.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/NinjaInputManagerComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

UNinjaInputHandler_Customization::UNinjaInputHandler_Customization()
{
	bCanBeBuffered = true;
	BufferChannelTag = FGameplayTag::RequestGameplayTag(TEXT("Input.Buffer.Customization"));
}

void UNinjaInputHandler_Customization::HandleTriggeredEvent_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value,
	const UInputAction* InputAction) const
{
	if (!Manager) return;

	// Reject processing if input value is non-boolean or inactive
	if (!Value.Get<bool>()) return;

	if (const APlayerController* PC = Cast<APlayerController>(Manager->GetController()); !PC) return;

	APawn* ControlledPawn = Manager->GetPawn();
	if (!ControlledPawn) return;

	APlayerState* PS = ControlledPawn->GetPlayerState();
	if (!PS) return;

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PS);
	if (!ASC) return;

	// Query matched tags bound to this input configuration
	FGameplayTagContainer TargetTags;
	GetGameplayTags(TargetTags);

	for (const FGameplayTag& Tag : TargetTags)
	{
		FGameplayEventData Payload;
		Payload.EventTag = Tag;
		Payload.Instigator = ControlledPawn;
		Payload.Target = PS;

		// Propose transaction to ASC; handoff boundary prevents direct state mutation from input thread
		ASC->HandleGameplayEvent(Tag, &Payload);
	}
}