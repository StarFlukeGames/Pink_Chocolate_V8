// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "Subsystem/GenericSibhdsSubsystem.h"

#include <string>

#include "GameplayTagContainer.h"

UGenericSibhdsSubsystem::UGenericSibhdsSubsystem()
{
}

std::expected<UObject*, EGenericDataError> UGenericSibhdsSubsystem::FetchDataNative(std::string_view DataKey) noexcept
{
	if (DataKey.empty())
	{
		return std::unexpected(EGenericDataError::InvalidData);
	}

	// Primary C++23 resolution or cache lookup
	return std::unexpected(EGenericDataError::NotFound);
}

UObject* UGenericSibhdsSubsystem::GetSubsystemData(const FString& DataKey)
{
	if (DataKey.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("[SIBHDS] GetSubsystemData requested with an empty key."));
		return nullptr;
	}

	// Bridge monadic std::expected to Unreal's reflection boundary
	const std::string NativeKey = TCHAR_TO_UTF8(*DataKey);
	const auto Result = FetchDataNative(NativeKey);

	return Result.value_or(nullptr);
}

bool UGenericSibhdsSubsystem::HasDataError(EGenericDataError ErrorCode) const
{
	return ErrorCode != EGenericDataError::None;
}

int32 UGenericSibhdsSubsystem::GetMaxOptionsForCategory(FGameplayTag CategoryTag) const
{
	return 0;
	// Rehydrate if query occurs before Initialize or after cache invalidation
	// if (CachedRoster.IsEmpty())
	// {
	// 	const_cast<UGenericSibhdsSubsystem*>(this)->IngestAndRehydrateRoster();
	// }
	//
	// auto CategoryOpt = FindCategoryByTag(CategoryTag);
	// return CategoryOpt.has_value() ? CategoryOpt->Options.Num() : 0;
}