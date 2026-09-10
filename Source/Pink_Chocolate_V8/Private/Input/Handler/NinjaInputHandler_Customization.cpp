// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "Input/Handler/NinjaInputHandler_Customization.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerState.h"
#include "GameplayTagAssetInterface.h"
#include "InputAction.h"
#include "Components/NinjaInputManagerComponent.h"

UNinjaInputHandler_Customization::UNinjaInputHandler_Customization()
{
}

void UNinjaInputHandler_Customization::HandleTriggeredEvent_Implementation(
	UNinjaInputManagerComponent* Manager,
	const FInputActionValue& Value,
	const UInputAction* InputAction,
	float ElapsedTime) const
{
	if (!Manager) return;

	bool bIsPressed = Value.Get<bool>();
	if (!bIsPressed) return;

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

		ASC->HandleGameplayEvent(Tag, &Payload);
	}
}