// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "Subsystem/GenericSibhdsSubsystem.h"

#include <string>

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
// #include "Misc/ConfigFile.h"

UGenericSibhdsSubsystem::UGenericSibhdsSubsystem()
{
}

std::expected<UObject*, EGenericDataError> UGenericSibhdsSubsystem::FetchDataNative(std::string_view DataKey) noexcept
{
	if (DataKey.empty())
	{
		return std::unexpected(EGenericDataError::InvalidData);
	}

	const FString KeyString = FString(UTF8_TO_TCHAR(DataKey.data()));

	// Perform primary C++23 data resolution or cache lookup
	// If resource is missing or unmapped:
	return std::unexpected(EGenericDataError::NotFound);
}

UObject* UGenericSibhdsSubsystem::GetSubsystemData(const FString& DataKey)
{
	if (DataKey.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("[SIBHDS] GetSubsystemData requested with an empty key."));
		return nullptr;
	}

	// Bridge standard C++23 std::expected with Unreal Engine's reflection boundary
	const std::string NativeKey = TCHAR_TO_UTF8(*DataKey);
	const auto Result = FetchDataNative(NativeKey);

	// Return contained UObject pointer or nullptr via C++23 value_or
	return Result.value_or(nullptr);
}

bool UGenericSibhdsSubsystem::HasDataError(EGenericDataError ErrorCode) const
{
	return ErrorCode != EGenericDataError::None;
}