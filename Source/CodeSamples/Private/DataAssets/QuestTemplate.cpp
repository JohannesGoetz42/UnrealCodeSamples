// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeSamples/Public/DataAssets/QuestTemplate.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeSamples/Public/Actors/Town.h"
#include "CodeSamples/Public/Components/LocationMarkerComponent.h"
#include "CodeSamples/Public/DataAssets/GeneratedQuestData.h"
#include "CodeSamples/Public/Interfaces/HasLocationMarker.h"
#include "CodeSamples/Public/Interfaces/QuestObjectiveTemplateData.h"
#include "UObject/ObjectSaveContext.h"

UGeneratedQuestData* UQuestTemplate::GenerateQuest(ATown* Town) const
{
	UGeneratedQuestData* GeneratedQuest = NewObject<UGeneratedQuestData>();
	GenerateObjectives(GeneratedQuest, Town);
	GenerateQuestLocations(GeneratedQuest, Town);
	GenerateReward(GeneratedQuest);
	GenerateTexts(GeneratedQuest);
	return GeneratedQuest;
}

void UQuestTemplate::GenerateObjectives(UGeneratedQuestData* OutGeneratedQuest, ATown* Town) const
{
	// Generate Parameters for every available objective
	for (const FQuestObjectiveParametersTemplate& ObjectiveParametersTemplate : AvailableObjectives)
	{
		// Find location source
		FGeneratedQuestObjectiveParameters ObjectiveParameters;
		ObjectiveParameters.QuestItems = QuestItems;
		if (!ObjectiveParametersTemplate.ObjectiveLocationTypes.IsEmpty())
		{
			ObjectiveParameters.ObjectiveLocationSource = FindLocationInstance(
				ObjectiveParametersTemplate.ObjectiveLocationTypes, Town);
			ensure(ObjectiveParameters.ObjectiveLocationSource);
		}

		// Generate spawn data for every spawned actor
		if (ObjectiveParametersTemplate.TotalSpawnedAmount > 0 && !ObjectiveParametersTemplate.SpawnedActors.IsEmpty())
		{
			uint32 RemainingAmount = ObjectiveParametersTemplate.TotalSpawnedAmount;
			TMap<TSubclassOf<AActor>, uint32> SpawnedAmounts;
			TArray<TSubclassOf<AActor>> AvailableTypes;
			ObjectiveParametersTemplate.SpawnedActors.GenerateKeyArray(AvailableTypes);

			// randomly distribute until the total spawned amount is reached
			while (RemainingAmount > 0)
			{
				const uint32 DistributedAmount = FMath::RandRange(1, RemainingAmount);
				const uint32 SpawnTypeIndex = FMath::RandRange(0, AvailableTypes.Num() - 1);
				uint32& CurrentAmount = SpawnedAmounts.FindOrAdd(AvailableTypes[SpawnTypeIndex]);
				CurrentAmount += DistributedAmount;
				RemainingAmount -= DistributedAmount;
			}
			
			// add the spawned amounts to the quest objective parameters
			for (const auto& SpawnedActor : SpawnedAmounts)
			{
				FQuestObjectiveSpawnData SpawnData;
				SpawnData.SpawnedAmount = SpawnedActor.Value;
				SpawnData.SpawnLocationTag = ObjectiveParametersTemplate.SpawnedActors.FindRef(SpawnedActor.Key);
				ObjectiveParameters.SpawnData.Add(SpawnedActor.Key, SpawnData);
			}
		}

		// instantiate an objective based on the generated parameters
		UDataAsset* Objective = NewObject<UDataAsset>(Town, ObjectiveParametersTemplate.ObjectiveClass);
		IQuestObjectiveTemplateData* GeneratedObjectiveData = Cast<IQuestObjectiveTemplateData>(Objective);
		if (ensure(GeneratedObjectiveData))
		{
			GeneratedObjectiveData->SetObjectiveParameters(ObjectiveParameters);
		}

		OutGeneratedQuest->QuestObjectives.Add(Objective);
	}
}

void UQuestTemplate::GenerateQuestLocations(UGeneratedQuestData* OutGeneratedQuest, const ATown* Town) const
{
	// Generate quest giver location
	const IHasLocationMarker* QuestGiverLocationSource = FindLocationInstance(QuestGiverLocationTypes, Town);
	if (ensure(QuestGiverLocationSource))
	{
		const ULocationMarkerComponent* LocationMarker = QuestGiverLocationSource->GetRandom(ELocationType::LT_NPC);
		if (ensure(LocationMarker))
		{
			OutGeneratedQuest->QuestGiverTransform = LocationMarker->GetComponentTransform();
		}
	}

	// Additional locations might get relevant at a later stage of development 
}

void UQuestTemplate::GenerateReward(UGeneratedQuestData* OutGeneratedQuest)
{
	// Player rewards are outside the scope of this code sample
	OutGeneratedQuest->Reward = FPlayerRewardData();
}

void UQuestTemplate::GenerateTexts(UGeneratedQuestData* OutGeneratedQuest) const
{
	OutGeneratedQuest->QuestName = QuestName.IsEmpty() ? FText::FromString("PLACEHOLDER") : QuestName;
	if (QuestText.IsEmpty())
	{
		OutGeneratedQuest->QuestTexts = {FText::FromString("PLACEHOLDER \n Sorry, there will probably be no reward.")};
	}
	else
	{
		OutGeneratedQuest->QuestTexts = {QuestText};
	}
}

const IHasLocationMarker* UQuestTemplate::FindLocationInstance(TArray<TSubclassOf<UObject>> LocationTypes,
															   const ATown* Town) const
{
	while (!LocationTypes.IsEmpty())
	{
		const int32 SelectedLocationIndex = FMath::RandRange(0, LocationTypes.Num() - 1);
		TSet<const IHasLocationMarker*> LocationSources;
		Town->GetLocationSources(LocationTypes[SelectedLocationIndex], LocationSources);
		if (!LocationSources.IsEmpty())
		{
			const int32 RandomIndex = FMath::RandRange(0, LocationSources.Num() - 1);
			return LocationSources.Array()[RandomIndex];
		}
		
		LocationTypes.RemoveAt(SelectedLocationIndex);
	}

	UE_LOG(LogTemp, Error, TEXT("Could not find a location for QuestTemplate '%s'!"), *GetName());
	checkNoEntry(); // implement instance search for location type!
	return nullptr;
}

#if WITH_EDITOR
void UQuestTemplate::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);

	// validate objectives
	for (FQuestObjectiveParametersTemplate& ObjectiveParameters : AvailableObjectives)
	{
		// validate Spawned actor assets
		if (const IQuestObjectiveTemplateData* GeneratedObjectiveData = Cast<IQuestObjectiveTemplateData>(
			ObjectiveParameters.ObjectiveClass.GetDefaultObject()))
		{
			TArray<TSubclassOf<AActor>> SpawnAssets;
			ObjectiveParameters.SpawnedActors.GetKeys(SpawnAssets);
			for (const TSubclassOf<AActor> SpawnAsset : SpawnAssets)
			{
				if (!ensure(GeneratedObjectiveData->IsValidSpawnAsset(SpawnAsset)))
				{
					UE_LOG(LogTemp, Error,
					       TEXT("QuestTemplate '%s' saved with invalid spawn actor '%s' for Objective class: '%s'!"),
					       *GetName(), *SpawnAsset->GetName(), *ObjectiveParameters.ObjectiveClass->GetName());
				}
			}
		}

		// ensure no null location types are saved
		ObjectiveParameters.ObjectiveLocationTypes.Remove(nullptr);
	}

	// ensure no null quest giver location types are saved
	QuestGiverLocationTypes.Remove(nullptr);
}
#endif
