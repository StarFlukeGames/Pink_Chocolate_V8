// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/PCCOptionTypes.h"
#include "PCCustomizationCatalog.generated.h"

/**
 * UPCCustomizationCatalog
 * Designer-authored master database of categories and cosmetic options [cite: 107].
 */
UCLASS(BlueprintType, Blueprintable)
class PINK_CHOCOLATE_V8_API UPCCustomizationCatalog : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization Schema")
	TArray<FPCCategoryDefinition> Categories;

	/**
	 * Resolves an option item using safe, out-of-bounds protected indexing [cite: 107].
	 */
	UFUNCTION(BlueprintPure, Category = "Customization Schema")
	bool GetOptionAtIndex(FGameplayTag CategoryTag, int32 Index, FPCOptionItem& OutOption) const;

	UFUNCTION(BlueprintPure, Category = "Customization Schema")
	int32 GetMaxOptionsForCategory(FGameplayTag CategoryTag) const;
};