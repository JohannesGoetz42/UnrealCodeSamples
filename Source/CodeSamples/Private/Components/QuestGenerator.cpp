// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeSamples/Public/Components/QuestGenerator.h"

#include "CodeSamples/Public/Constants.h"
#include "CodeSamples/Public/Actors/InteractionCharacter.h"
#include "CodeSamples/Public/Actors/Town.h"
#include "CodeSamples/Public/Components/QuestComponent.h"
#include "CodeSamples/Public/Components/QuestGiverComponent.h"
#include "CodeSamples/Public/DataAssets/GeneratedQuestData.h"
#include "CodeSamples/Public/DataAssets/QuestTemplate.h"

void UQuestGenerator::UnlockQuestTemplate(TSubclassOf<UQuestTemplate> QuestToUnlock)
{
	// do not unlock if a quest with the same template is already active
	for (const auto& Quest : CurrentQuests)
	{
		if (Quest.Value.Template == QuestToUnlock)
		{
			return;
		}
	}

	AvailableQuestTemplates.Add(QuestToUnlock);
	if (!GetWorld()->GetTimerManager().IsTimerActive(GenerateQuestTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(GenerateQuestTimer, this, &UQuestGenerator::GenerateQuest,
		                                       RandomizeQuestSpawnInterval(), false);
	}
}

void UQuestGenerator::ReactToQuestAccepted(UQuestComponent* QuestComponent)
{
	if (ensure(QuestComponent->GetQuestData()->IsA<UGeneratedQuestData>()))
	{
		QuestComponent->OnQuestCompleted.AddUObject(this, &UQuestGenerator::ReactToQuestCompleted);
	}
}

void UQuestGenerator::GenerateQuest()
{
	if (CurrentQuests.Num() >= MaximumAvailableQuests || AvailableQuestTemplates.IsEmpty())
	{
		GetWorld()->GetTimerManager().ClearTimer(GenerateQuestTimer);
		return;
	}

	const int32 SelectedTemplateIndex = FMath::RandRange(0, AvailableQuestTemplates.Num() - 1);
	const UQuestTemplate* SelectedTemplate = AvailableQuestTemplates[SelectedTemplateIndex].GetDefaultObject();
	if (ensure(IsValid(SelectedTemplate)))
	{
		SpawnQuestGiver(SelectedTemplate);
	}

	GetWorld()->GetTimerManager().SetTimer(GenerateQuestTimer, this, &UQuestGenerator::GenerateQuest,
	                                       RandomizeQuestSpawnInterval(), false);
}

void UQuestGenerator::ReactToQuestCompleted(const UQuestComponent* QuestComponent)
{
	const UGeneratedQuestData* Quest = Cast<UGeneratedQuestData>(QuestComponent->GetQuestData());
	if (ensure(Quest))
	{
		FGeneratedQuestState QuestState;
		CurrentQuests.RemoveAndCopyValue(Quest, QuestState);
		if (ensure(QuestState.QuestGiver))
		{
			QuestState.QuestGiver->Destroy();
		}

		AvailableQuestTemplates.Add(QuestState.Template);
	}

	if (!GetWorld()->GetTimerManager().IsTimerActive(GenerateQuestTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(GenerateQuestTimer, this, &UQuestGenerator::GenerateQuest,
		                                       RandomizeQuestSpawnInterval(), false);
	}
}

AInteractionCharacter* UQuestGenerator::SpawnQuestGiver(const UQuestTemplate* QuestTemplate)
{
	if (IsValid(QuestTemplate))
	{
		TSubclassOf<AInteractionCharacter> SelectedQuestGiverClass = QuestTemplate->QuestGiverClass;
		if (!SelectedQuestGiverClass)
		{
			SelectedQuestGiverClass = DefaultQuestGiverClass;
		}

		if (ATown* Town = Cast<ATown>(GetOwner()))
		{
			const UGeneratedQuestData* GeneratedQuest = QuestTemplate->GenerateQuest(Town);
			FTransform SpawnTransform = GeneratedQuest->QuestGiverTransform;
			SpawnTransform.AddToTranslation(CHARACTER_SPAWN_HEIGHT);

			// Spawn the quest giver
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.bNoFail = true;			
			if (AInteractionCharacter* SpawnedQuestGiver = GetWorld()->SpawnActor<AInteractionCharacter>(
				SelectedQuestGiverClass, SpawnTransform, SpawnParameters); ensure(SpawnedQuestGiver))
			{
				// get or add a quest giver component 
				UQuestGiverComponent* QuestGiverComponent = Cast<UQuestGiverComponent>(
					SpawnedQuestGiver->GetComponentByClass(UQuestGiverComponent::StaticClass()));
				if (!QuestGiverComponent)
				{
					QuestGiverComponent = NewObject<
						UQuestGiverComponent>(SpawnedQuestGiver, FName("Quest Giver Component"));
					QuestGiverComponent->RegisterComponent();
				}
				QuestGiverComponent->SetQuest(GeneratedQuest);

				// remember the generated quest
				FGeneratedQuestState QuestState;
				QuestState.QuestGiver = SpawnedQuestGiver;
				QuestState.Template = QuestTemplate->GetClass();
				CurrentQuests.Add(GeneratedQuest, QuestState);

				// remove the template from the available templates until it is completed
				AvailableQuestTemplates.Remove(QuestTemplate->GetClass());

				return SpawnedQuestGiver;
			}
		}
	}

	checkNoEntry();
	return nullptr;
}

void UQuestGenerator::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(GenerateQuestTimer, this, &UQuestGenerator::GenerateQuest,
	                                       RandomizeQuestSpawnInterval(), false);
}
