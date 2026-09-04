// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "NinjaInputHandler.h"
#include "NinjaInputHandler_Customization.generated.h"

class UNinjaInputManagerComponent;

/**
 * UNinjaInputHandler_Customization
 *
 * Stateless hardware translation handler for character customization mapping.
 * Normalizes physical arrow and enter keystrokes into clean GAS Gameplay Tag events.
 */
UCLASS(Blueprintable, BlueprintType)
class PINK_CHOCOLATE_V8_API UNinjaInputHandler_Customization : public UNinjaInputHandler
{
	GENERATED_BODY()

public:
	UNinjaInputHandler_Customization();

	/**
	 * Native implementation of input handling.
	 * Enforces the const-correctness contract from the latest Ninja Bear IPT.
	 */
	virtual void HandleTriggeredEvent_Implementation(
		UNinjaInputManagerComponent* Manager,
		const FInputActionValue& Value,
		const UInputAction* InputAction) const override;
};