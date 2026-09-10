// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/FOSibhdsTypes.h"
#include <optional>
#include "PCCustomizationCatalog.generated.h"

/**
 * UPCCustomizationCatalog
 * Authoritative, non-volatile database of all category schemas and options.
 */
UCLASS(BlueprintType, Const, Blueprintable)
class PINK_CHOCOLATE_V8_API UPCCustomizationCatalog : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SIBHDS Catalog", meta = (TitleProperty = "CategoryTag"))
	TArray<FPCCategoryDefinition> Categories;

	/** Monadic C++23 lookup of a category by its Gameplay Tag (Hidden from UHT) */
	[[nodiscard]] std::optional<FPCCategoryDefinition> FindCategoryByTag(const FGameplayTag& CategoryTag) const noexcept;

	UFUNCTION(BlueprintPure, Category = "SIBHDS Catalog")
	bool GetOptionAtIndex(FGameplayTag CategoryTag, int32 Index, FPCOptionItem& OutOption) const;

	UFUNCTION(BlueprintPure, Category = "SIBHDS Catalog")
	int32 GetMaxOptionsForCategory(FGameplayTag CategoryTag) const;
};