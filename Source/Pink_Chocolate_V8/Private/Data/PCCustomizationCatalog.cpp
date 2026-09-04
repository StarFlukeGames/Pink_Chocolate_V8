// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "Data/PCCustomizationCatalog.h"

std::optional<FPCCategoryDefinition> UPCCustomizationCatalog::FindCategoryByTag(const FGameplayTag& CategoryTag) const noexcept
{
	for (const FPCCategoryDefinition& Category : Categories)
	{
		if (Category.CategoryTag == CategoryTag)
		{
			return Category;
		}
	}
	return std::nullopt;
}

bool UPCCustomizationCatalog::GetOptionAtIndex(FGameplayTag CategoryTag, int32 Index, FPCOptionItem& OutOption) const
{
	auto CategoryOpt = FindCategoryByTag(CategoryTag);
	if (CategoryOpt.has_value())
	{
		const FPCCategoryDefinition& Category = *CategoryOpt;
		if (Category.Options.IsValidIndex(Index))
		{
			OutOption = Category.Options[Index];
			return true;
		}
	}
	return false;
}

int32 UPCCustomizationCatalog::GetMaxOptionsForCategory(FGameplayTag CategoryTag) const
{
	auto CategoryOpt = FindCategoryByTag(CategoryTag);
	return CategoryOpt.has_value() ? CategoryOpt->Options.Num() : 0;
}