// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/SoftObjectPath.h"
#include <concepts>
#include <type_traits>
#include "FOSibhdsTypes.generated.h"

/**
 * Compile-time C++23 concept ensuring that only UObject-derived 
 * classes can be targeted by our polymorphic resolution handlers.
 */
template <typename T>
concept UObjectDerived = std::is_base_of_v<UObject, T>;

/**
 * EPCOptionType
 * Specifies the underlying asset class of the polymorphic Soft Path.
 */
UENUM(BlueprintType)
enum class EPCOptionType : uint8
{
    Material          UMETA(DisplayName = "Material Override"),
    SkeletalMesh      UMETA(DisplayName = "Skeletal Mesh Attachment"),
    NiagaraSystem     UMETA(DisplayName = "Niagara VFX System"),
    CharacterClass    UMETA(DisplayName = "Character Class Roster Swap"),
    BlueprintWrapper  UMETA(DisplayName = "Actor Blueprint Wrapper")
};

/**
 * FPCOptionItem
 * Collapsed, non-verbose option structure with a single polymorphic soft asset path.
 * Replaced in memory during bulk ingestion via the generic reflection-driven pipeline.
 */
USTRUCT(BlueprintType)
struct PINK_CHOCOLATE_V8_API FPCOptionItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sovereign Customization | Option")
    FName OptionId;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sovereign Customization | Option")
    FText DisplayName;

    /**
     * Polymorphic asset pointer. Points to materials, meshes, Niagara emitters, or classes.
     * Avoids verbose parallel pointer definitions by resolving path dynamically at runtime.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sovereign Customization | Option")
    FSoftObjectPath AssetPath;
    
    [[nodiscard]] bool IsValid() const noexcept
    {
        return !OptionId.IsNone() && AssetPath.IsValid();
    }/**
     * Inline friend operator enables Argument-Dependent Lookup (ADL)
     * across all FArchive derivatives, including FMemoryReader and FMemoryWriter.
     */
    friend FArchive& operator<<(FArchive& Ar, FPCOptionItem& Item)
    {
        Ar << Item.OptionId;
        Ar << Item.DisplayName;
        Ar << Item.AssetPath;
        return Ar;
    }
};

/**
 * FPCCategoryDefinition
 * Pairs an extensible tag category with its type constraint and option set.
 */
USTRUCT(BlueprintType)
struct PINK_CHOCOLATE_V8_API FPCCategoryDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sovereign Customization | Category")
    FGameplayTag CategoryTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sovereign Customization | Category")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sovereign Customization | Category")
    EPCOptionType OptionType = EPCOptionType::Material;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sovereign Customization | Category")
    TArray<FPCOptionItem> Options;
    
    friend FArchive& operator<<(FArchive& Ar, FPCCategoryDefinition& Category)
    {
        Ar << Category.CategoryTag;
        Ar << Category.DisplayName;
        Ar << Category.Options; // Recursively invokes FPCOptionItem operator<<
        return Ar;
    }
};