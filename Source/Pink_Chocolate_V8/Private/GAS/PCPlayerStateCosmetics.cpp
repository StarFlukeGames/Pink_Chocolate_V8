// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "GAS/PCPlayerStateCosmetics.h"
#include "AbilitySystemComponent.h"
#include "GAS/CustomizationAttributeSet.h"
#include "Net/UnrealNetwork.h"

APCPlayerStateCosmetics::APCPlayerStateCosmetics()
{
    bReplicates = true;
    NetUpdateFrequency = 100.0f; // Raise to guarantee sub-millisecond tag propagation

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

    AttributeSetCustomization = CreateDefaultSubobject<UCustomizationAttributeSet>(TEXT("AttributeSetCustomization"));
}

void APCPlayerStateCosmetics::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APCPlayerStateCosmetics, CosmeticSelections);
}

UAbilitySystemComponent* APCPlayerStateCosmetics::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void APCPlayerStateCosmetics::SetCosmeticSelection(FGameplayTag CategoryTag, int32 NewIndex)
{
    for (FPCCosmeticSelection& Selection : CosmeticSelections)
    {
        if (Selection.CategoryTag == CategoryTag)
        {
            Selection.SelectedIndex = NewIndex;
            OnCosmeticSelectionChanged.Broadcast(CategoryTag, NewIndex);
            return;
        }
    }

    FPCCosmeticSelection NewSelection;
    NewSelection.CategoryTag = CategoryTag;
    NewSelection.SelectedIndex = NewIndex;
    CosmeticSelections.Add(NewSelection);

    OnCosmeticSelectionChanged.Broadcast(CategoryTag, NewIndex);
}

int32 APCPlayerStateCosmetics::GetCosmeticSelection(FGameplayTag CategoryTag) const
{
    for (const FPCCosmeticSelection& Selection : CosmeticSelections)
    {
        if (Selection.CategoryTag == CategoryTag)
        {
            return Selection.SelectedIndex;
        }
    }
    return 0;
}

void APCPlayerStateCosmetics::OnRep_CosmeticSelections()
{
    for (const FPCCosmeticSelection& Selection : CosmeticSelections)
    {
        OnCosmeticSelectionChanged.Broadcast(Selection.CategoryTag, Selection.SelectedIndex);
    }
}