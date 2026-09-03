// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/SkeletalMesh.h"
#include "Materials/MaterialInterface.h"
#include "GameFramework/Pawn.h"
#include "PCCOptionTypes.generated.h"

UENUM(BlueprintType)
enum class EPCOptionType : uint8
{
    Material       UMETA(DisplayName = "Material Override"),
    SkeletalMesh   UMETA(DisplayName = "Skeletal Mesh Swap"),
    CharacterClass UMETA(DisplayName = "Character Class Roster Swap")
};

/**
 * FPCOptionItem
 * Represents a single customizable cosmetic option or roster pawn [cite: 107, 300].
 */
USTRUCT(BlueprintType)
struct PINK_CHOCOLATE_V8_API FPCOptionItem
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization")
    FName OptionId;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization", meta = (AllowedClasses = "/Script/Engine.SkeletalMesh"))
    TSoftObjectPtr<USkeletalMesh> MeshAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization", meta = (AllowedClasses = "/Script/Engine.MaterialInterface"))
    TSoftObjectPtr<UMaterialInterface> MaterialAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization")
    TSoftClassPtr<APawn> CharacterClass;
};

/**
 * FPCCategoryDefinition
 * Defines an entire customization category and its options array [cite: 4, 107].
 */
USTRUCT(BlueprintType)
struct PINK_CHOCOLATE_V8_API FPCCategoryDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization")
    FGameplayTag CategoryTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization")
    EPCOptionType OptionType = EPCOptionType::Material;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Customization")
    TArray<FPCOptionItem> Options;
};