// Copyright (c) StarFluke Fallen World. All Rights Reserved.
#include "GAS/PCPlayerStateCosmetics.h"
#include "Net/UnrealNetwork.h"

APCPlayerStateCosmetics::APCPlayerStateCosmetics()
{
	bReplicates = true;
}

void APCPlayerStateCosmetics::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APCPlayerStateCosmetics, CosmeticSelections);
}

void APCPlayerStateCosmetics::SetCosmeticSelection(FGameplayTag CategoryTag, int32 NewIndex)
{
	for (FPCCosmeticSelection& Selection : CosmeticSelections)
	{
		if (Selection.CategoryTag == CategoryTag)
		{
			Selection.SelectedIndex = NewIndex;
			OnCosmeticSelectionChanged.Broadcast(CategoryTag, NewIndex);
			return;
		}
	}

	// Add dynamically if Category did not exist previously! [cite: 4, 107]
	FPCCosmeticSelection NewSelection;
	NewSelection.CategoryTag = CategoryTag;
	NewSelection.SelectedIndex = NewIndex;
	CosmeticSelections.Add(NewSelection);

	OnCosmeticSelectionChanged.Broadcast(CategoryTag, NewIndex);
}

int32 APCPlayerStateCosmetics::GetCosmeticSelection(FGameplayTag CategoryTag) const
{
	for (const FPCCosmeticSelection& Selection : CosmeticSelections)
	{
		if (Selection.CategoryTag == CategoryTag)
		{
			return Selection.SelectedIndex;
		}
	}
	return 0; // Safe fallback [cite: 14, 519]
}

void APCPlayerStateCosmetics::OnRep_CosmeticSelections()
{
	// Fire delegates locally on client to trigger event-driven UI updates [cite: 336, 338]
	for (const FPCCosmeticSelection& Selection : CosmeticSelections)
	{
		OnCosmeticSelectionChanged.Broadcast(Selection.CategoryTag, Selection.SelectedIndex);
	}
}