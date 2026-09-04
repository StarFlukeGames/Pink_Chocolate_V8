// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CustomizationAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * UCustomizationAttributeSet
 * Exposes cosmetic index attributes to the Gameplay Ability System.
 */
UCLASS()
class PINK_CHOCOLATE_V8_API UCustomizationAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCustomizationAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Customization | Attributes")
	FGameplayAttributeData HeadMaterialIndex;
	ATTRIBUTE_ACCESSORS(UCustomizationAttributeSet, HeadMaterialIndex)

	UPROPERTY(BlueprintReadOnly, Category = "Customization | Attributes")
	FGameplayAttributeData PantsMaterialIndex;
	ATTRIBUTE_ACCESSORS(UCustomizationAttributeSet, PantsMaterialIndex)

	UPROPERTY(BlueprintReadOnly, Category = "Customization | Attributes")
	FGameplayAttributeData ThrustNiagaraIndex;
	ATTRIBUTE_ACCESSORS(UCustomizationAttributeSet, ThrustNiagaraIndex)

	UPROPERTY(BlueprintReadOnly, Category = "Customization | Attributes")
	FGameplayAttributeData ActiveRosterIndex;
	ATTRIBUTE_ACCESSORS(UCustomizationAttributeSet, ActiveRosterIndex)
};