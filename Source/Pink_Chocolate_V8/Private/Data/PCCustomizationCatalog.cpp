// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "Data/PCCustomizationCatalog.h"

bool UPCCustomizationCatalog::GetOptionAtIndex(FGameplayTag CategoryTag, int32 Index, FPCOptionItem& OutOption) const
{
	for (const FPCCategoryDefinition& Category : Categories)
	{
		if (Category.CategoryTag == CategoryTag)
		{
			if (Category.Options.IsValidIndex(Index))
			{
				OutOption = Category.Options[Index];
				return true;
			}
			break;
		}
	}
	return false;
}

int32 UPCCustomizationCatalog::GetMaxOptionsForCategory(FGameplayTag CategoryTag) const
{
	for (const FPCCategoryDefinition& Category : Categories)
	{
		if (Category.CategoryTag == CategoryTag)
		{
			return Category.Options.Num();
		}
	}
	return 0;
}