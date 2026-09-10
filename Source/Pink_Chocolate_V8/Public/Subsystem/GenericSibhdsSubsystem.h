#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/MemoryWriter.h"
// #include "PCCustomizationTypes.h" // Contains FPinkChocolateSchemaBinaryEnvelope
#include <expected>
#include <string_view>
#include "GenericSibhdsSubsystem.generated.h"

/** SIBHDS Data Error Codes */
UENUM(BlueprintType)
enum class EGenericDataError : uint8
{
    None            UMETA(DisplayName = "None"),
    NotFound        UMETA(DisplayName = "Not Found"),
    InvalidData     UMETA(DisplayName = "Invalid Data"),
    ReadFailure     UMETA(DisplayName = "Read Failure")
};

/**
 * UGenericSibhdsSubsystem
 * Subsystem governing INI-Binary hybrid data ingestion and binary envelope persistence.
 */
UCLASS()
class PINK_CHOCOLATE_V8_API UGenericSibhdsSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    UGenericSibhdsSubsystem();

    // ========================================================================
    // C++23 MONADIC & TEMPLATE API (NO UFUNCTION MACROS)
    // ========================================================================

    /**
     * Native C++23 monadic data resolution pipeline.
     * MUST NOT be marked with UFUNCTION().
     */
    std::expected<UObject*, EGenericDataError> FetchDataNative(std::string_view DataKey) noexcept;

    /**
     * Pure C++ template serialization for SIBHDS schema envelopes.
     * MUST NOT be marked with UFUNCTION().
     */
    template <typename T>
    bool SerializeEnvelope(const T& InSchema, TArray<uint8>& OutBinaryBuffer)
    {
        FMemoryWriter Writer(OutBinaryBuffer, true);
        Writer << const_cast<T&>(InSchema);
        return OutBinaryBuffer.Num() > 0;
    }

    /**
     * Pure C++ template deserialization using ADL operator<<.
     * MUST NOT be marked with UFUNCTION().
     */
    template <typename T>
    bool DeserializeEnvelope(const TArray<uint8>& InBinaryBuffer, T& OutSchema)
    {
        if (InBinaryBuffer.IsEmpty())
        {
            return false;
        }

        FMemoryReader Reader(InBinaryBuffer, true);
        Reader << OutSchema; // Resolves friend FArchive& operator<< via ADL
        return true;
    }

    // ========================================================================
    // BLUEPRINT REFLECTION BOUNDARY (UHT / UFUNCTION APPROVED)
    // ========================================================================

    /**
     * Reflection wrapper exposing C++23 monadic fetch to Blueprints.
     */
    UFUNCTION(BlueprintCallable, Category = "SIBHDS | Subsystem")
    UObject* GetSubsystemData(const FString& DataKey);

    /**
     * Error checking helper for Blueprint graphs.
     */
    UFUNCTION(BlueprintPure, Category = "SIBHDS | Subsystem")
    bool HasDataError(EGenericDataError ErrorCode) const;
};