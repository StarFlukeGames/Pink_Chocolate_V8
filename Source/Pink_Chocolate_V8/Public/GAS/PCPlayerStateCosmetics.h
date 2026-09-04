// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include <expected>
#include "PCPlayerStateCosmetics.generated.h"

class UAbilitySystemComponent;
class UCustomizationAttributeSet;

USTRUCT(BlueprintType)
struct FPCCosmeticSelection
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    FGameplayTag CategoryTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
    int32 SelectedIndex = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCosmeticSelectionChangedSignature, FGameplayTag, CategoryTag, int32, NewIndex);

UCLASS()
class PINK_CHOCOLATE_V8_API APCPlayerStateCosmetics : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    APCPlayerStateCosmetics();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "Pink Chocolate | Cosmetics")
    void SetCosmeticSelection(FGameplayTag CategoryTag, int32 NewIndex);

    UFUNCTION(BlueprintPure, Category = "Pink Chocolate | Cosmetics")
    int32 GetCosmeticSelection(FGameplayTag CategoryTag) const;

    UPROPERTY(BlueprintAssignable, Category = "Pink Chocolate | Cosmetics")
    FOnCosmeticSelectionChangedSignature OnCosmeticSelectionChanged;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pink Chocolate | GAS")
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UCustomizationAttributeSet> AttributeSetCustomization;

    UPROPERTY(ReplicatedUsing = OnRep_CosmeticSelections, BlueprintReadOnly, Category = "Pink Chocolate | Cosmetics")
    TArray<FPCCosmeticSelection> CosmeticSelections;

    UFUNCTION()
    void OnRep_CosmeticSelections();
};