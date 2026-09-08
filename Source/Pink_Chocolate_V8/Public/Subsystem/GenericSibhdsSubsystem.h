// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

// Standard C++23 headers MUST be included BEFORE .generated.h
#include <expected>
#include <optional>
#include <string_view>
#include <concepts>

#include "GenericSibhdsSubsystem.generated.h" // Must be the absolute last include

/**
 * Reflected error enum for Blueprint and UHT recognition.
 * Declared outside the class so UHT generates Z_Construct_UEnum properly.
 */
UENUM(BlueprintType)
enum class EGenericDataError : uint8
{
    None        UMETA(DisplayName = "None"),
    NotFound    UMETA(DisplayName = "Not Found"),
    InvalidData UMETA(DisplayName = "Invalid Data"),
    Unknown     UMETA(DisplayName = "Unknown Error")
};

/**
 * UGenericSibhdsSubsystem
 */
UCLASS(Blueprintable, BlueprintType)
class PINK_CHOCOLATE_V8_API UGenericSibhdsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UGenericSibhdsSubsystem();

    // ------------------------------------------------------------------------
    // 1. Blueprint-Exposed Interface (UHT Compatible Types Only)
    // ------------------------------------------------------------------------

    /** Blueprint wrapper returning UObject pointer safely */
    UFUNCTION(BlueprintCallable, Category = "SIBHDS Subsystem")
    UObject* GetSubsystemData(const FString& DataKey);

    /** Blueprint wrapper for error status check */
    UFUNCTION(BlueprintPure, Category = "SIBHDS Subsystem")
    bool HasDataError(EGenericDataError ErrorCode) const;

    // ------------------------------------------------------------------------
    // 2. Safe C++23 Pure Native Interface (NO UFUNCTION / UPROPERTY MACROS!)
    // ------------------------------------------------------------------------

    /** Safe C++23 transactional method using std::expected (Hidden from UHT) */
    std::expected<UObject*, EGenericDataError> FetchDataNative(std::string_view DataKey) noexcept;

    /** Safe C++23 concept-constrained helper (Hidden from UHT) */
    template <typename T>
    requires std::derived_from<T, UObject>
    T* ResolveDataTyped(std::string_view DataKey)
    {
        UObject* RawObj = GetSubsystemData(FString(DataKey.data()));
        return Cast<T>(RawObj);
    }
};