// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "NinjaInputHandler.h"
#include "NinjaInputHandler_Customization.generated.h"

/**
 * UNinjaInputHandler_Customization
 * Stateless hardware translation handler for character customization mapping [cite: 26].
 */
UCLASS(Blueprintable, BlueprintType)
class PINK_CHOCOLATE_V8_API UNinjaInputHandler_Customization : public UNinjaInputHandler
{
	GENERATED_BODY()

public:
	UNinjaInputHandler_Customization();

	/** 
	 * Native 4-parameter triggered input hook [cite: 22].
	 * Matches the const-correct execution contract of Ninja Input 5.8.2 [cite: 22].
	 */
	virtual void HandleTriggeredEvent_Implementation(
		UNinjaInputManagerComponent* Manager,
		const FInputActionValue& Value,
		const UInputAction* InputAction,
		float ElapsedTime) const override;
};