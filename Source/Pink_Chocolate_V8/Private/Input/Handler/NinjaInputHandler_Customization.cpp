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
    // Enforce Invariant NI-01: Ensure this class remains stateless [cite: 10].
}

void UNinjaInputHandler_Customization::HandleTriggeredEvent_Implementation(
    UNinjaInputManagerComponent* Manager,
    const FInputActionValue& Value,
    const UInputAction* InputAction,
    float ElapsedTime) const
{
    if (!Manager) return;

    // Filter digital false/release states (only process pressed/triggered events)
    bool bIsPressed = Value.Get<bool>();
    if (!bIsPressed) return;

    // Retrieve generic controller directly from the Manager context [cite: 23, 25]
    const AController* Controller = Manager->GetController();
    if (!Controller) return;

    // Locate possessed pawn and its persistent PlayerState
    APawn* ControlledPawn = Controller->GetPawn();
    if (!ControlledPawn) return;

    APlayerState* PS = ControlledPawn->GetPlayerState();
    if (!PS) return;

    // Resolve Ability System Component hosted on the PlayerState
    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(PS);
    if (!ASC) return;

    // Resolve target tags dynamically via IGameplayTagAssetInterface [cite: 25]
    FGameplayTagContainer InputTags;

    if (InputAction)
    {
        if (const IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(InputAction))
        {
            TagInterface->GetOwnedGameplayTags(InputTags);
        }
    }

    // Fallback: If InputAction is untagged, check if this Handler data asset has tags attached [cite: 25]
    if (InputTags.IsEmpty())
    {
        if (const IGameplayTagAssetInterface* HandlerTagInterface = Cast<IGameplayTagAssetInterface>(this))
        {
            HandlerTagInterface->GetOwnedGameplayTags(InputTags);
        }
    }

    // Marshal resolved tags as Gameplay Events directly to the ASC
    for (const FGameplayTag& Tag : InputTags)
    {
        FGameplayEventData Payload;
        Payload.EventTag = Tag;
        Payload.Instigator = ControlledPawn;
        Payload.Target = PS;

        ASC->HandleGameplayEvent(Tag, &Payload);
    }
}