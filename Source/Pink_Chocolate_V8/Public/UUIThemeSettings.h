// UIThemeSettings.h (UE 5.8.3 Integration)
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Fonts/SlateFontInfo.h"
#include "UObject/SoftObjectPtr.h"
#include "UUIThemeSettings.generated.h"

UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "StarFluke UI Theme Settings"))
class PINK_CHOCOLATE_V8_API UUIThemeSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Typography")
	FSlateFontInfo BodyFontInfo; // Exo2 SemiBold

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Typography")
	FSlateFontInfo HeaderFontInfo; // Exo2 Bold

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Glyphs")
	TSoftObjectPtr<UObject> StandardGlyphRegistry; // GR_Phosphor_Bold

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Glyphs")
	TSoftObjectPtr<UObject> ActiveGlyphRegistry; // GR_Phosphor_Fill

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Style & Palette")
	FLinearColor AccentCyan = FLinearColor(0.0f, 0.847f, 1.0f, 1.0f); // #00D8FF

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Style & Palette")
	FLinearColor HighlightPurple = FLinearColor(0.69f, 0.0f, 1.0f, 1.0f); // #B000FF

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Style & Palette")
	float CornerRadius = 8.0f;
};