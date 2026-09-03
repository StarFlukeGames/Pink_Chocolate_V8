// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameplayTagContainer.h"
#include "PCPlayerStateCosmetics.generated.h"

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

/**
 * APCPlayerStateCosmetics
 * Extensible PlayerState hosting active selection state indices [cite: 53, 339].
 */
UCLASS()
class PINK_CHOCOLATE_V8_API APCPlayerStateCosmetics : public APlayerState
{
	GENERATED_BODY()

public:
	APCPlayerStateCosmetics();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Pink Chocolate | Cosmetics")
	void SetCosmeticSelection(FGameplayTag CategoryTag, int32 NewIndex);

	UFUNCTION(BlueprintPure, Category = "Pink Chocolate | Cosmetics")
	int32 GetCosmeticSelection(FGameplayTag CategoryTag) const;

	UPROPERTY(BlueprintAssignable, Category = "Pink Chocolate | Cosmetics")
	FOnCosmeticSelectionChangedSignature OnCosmeticSelectionChanged;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CosmeticSelections, BlueprintReadOnly, Category = "Pink Chocolate | Cosmetics")
	TArray<FPCCosmeticSelection> CosmeticSelections;

	UFUNCTION()
	void OnRep_CosmeticSelections();
};