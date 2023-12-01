// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestTemplate.generated.h"

class IHasLocationMarker;
class ATown;
class UGeneratedQuestData;
class UTradeableItem;
class AInteractionCharacter;

USTRUCT(Blueprintable)
/**
 * This is an objective agnostic wrapper for the quest objective template.
 * This is used by the UQuestGenerator to generate a Quest objective (see FGeneratedQuestObjectiveParameters) at runtime.
 */
struct FQuestObjectiveParametersTemplate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (MustImplement = "/Script/BootyIsland.HasLocationMarker"))
	/** The object instances where objective actors can be spawned (i.E. buildings of a specific type) */
	TArray<TSubclassOf<UObject>> ObjectiveLocationTypes;
	UPROPERTY(EditDefaultsOnly)
	/** The spawned actors with optional spawn location tag (i.E. spawned PickUps) */
	TMap<TSubclassOf<AActor>, FName> SpawnedActors;
	UPROPERTY(EditDefaultsOnly)
	/** The total spawned amount randomly distributed over all SpawnedActor classes (i.E. total amount of spawned PickUps) */
	uint32 TotalSpawnedAmount = 1;
	UPROPERTY(EditDefaultsOnly,
		meta = (MustImplement = "/Script/BootyIsland.GeneratedQuestObjectiveData", Category = "Objective"))
	/** The base class of the quest objective (i.E collect PickUp objective) */
	TSubclassOf<UDataAsset> ObjectiveClass;
};

/**
 * Template for generated quests see also UGeneratedQuestData
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class CODESAMPLES_API UQuestTemplate : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	/** The class of the spawned quest giver. Falls back to a default if left empty. */
	TSubclassOf<AInteractionCharacter> QuestGiverClass = nullptr;
	UPROPERTY(EditAnywhere, meta = (MustImplement = "/Script/BootyIsland.HasLocationMarker"))
	/** The object types where objective actors can be spawned (i.E. buildings of a specific type) */
	TArray<TSubclassOf<UObject>> QuestGiverLocationTypes;
	UPROPERTY(EditAnywhere)
	/** The objectives that will be generated when a quest is generated from this template */
	TArray<FQuestObjectiveParametersTemplate> AvailableObjectives;
	UPROPERTY(EditDefaultsOnly)
	/** The name of the generated quests */
	FText QuestName;
	UPROPERTY(EditDefaultsOnly)
	/** The name of the generated quests TODO: generate quest texts from text blocks */
	FText QuestText;
	UPROPERTY(EditDefaultsOnly)
	/** Quest items relevant for multiple objectives, like pick up and delivery */
	TMap<TSubclassOf<UTradeableItem>, uint32> QuestItems;
	
	UGeneratedQuestData* GenerateQuest(ATown* Town) const;

protected:
	static void GenerateReward(UGeneratedQuestData* OutGeneratedQuest);
	
	void GenerateObjectives(UGeneratedQuestData* OutGeneratedQuest, ATown* Town) const;
	void GenerateQuestLocations(UGeneratedQuestData* OutGeneratedQuest, const ATown* Town) const;
	void GenerateTexts(UGeneratedQuestData* OutGeneratedQuest) const;
	const IHasLocationMarker* FindLocationInstance(TArray<TSubclassOf<UObject>> LocationTypes, const ATown* Town) const;
	
#if WITH_EDITOR
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
#endif
};
