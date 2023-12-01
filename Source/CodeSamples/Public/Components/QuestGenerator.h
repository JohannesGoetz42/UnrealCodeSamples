// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestGenerator.generated.h"


class UGeneratedQuestData;
class AInteractionCharacter;
class UQuestTemplate;

USTRUCT()
struct FGeneratedQuestState
{
	GENERATED_BODY()
	
	UPROPERTY()
	AInteractionCharacter* QuestGiver;
	UPROPERTY()
	TSubclassOf<UQuestTemplate> Template;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CODESAMPLES_API UQuestGenerator : public UActorComponent
{
	GENERATED_BODY()

public:
	void UnlockQuestTemplate(TSubclassOf<UQuestTemplate> TemplateToUnlock);
	void ReactToQuestAccepted(UQuestComponent* QuestComponent);

protected:
	UPROPERTY(EditAnywhere)
	/** The quest giver that is spawned when the template does not specify a specific one */
	TSubclassOf<AInteractionCharacter> DefaultQuestGiverClass;
	UPROPERTY(EditAnywhere)
	/** The quests that can be made available */
	TArray<TSubclassOf<UQuestTemplate>> AvailableQuestTemplates;
	UPROPERTY(EditAnywhere)
	int32 MaximumAvailableQuests = 5;
	UPROPERTY(EditAnywhere, meta = (ClampMin=0.0f))
	/** The base interval between quest spawns */
	float QuestSpawnInterval = 60.0f;
	UPROPERTY(EditAnywhere, meta = (ClampMin=0.0f))
	/** The maximum derivation of the quest spawn interval */
	float QuestSpawnDerivation = 30.0f;
	UPROPERTY()
	/** The quests that are currently available */
	TMap<const UGeneratedQuestData*, FGeneratedQuestState> CurrentQuests;

	FTimerHandle GenerateQuestTimer;
	
	UFUNCTION()
	void GenerateQuest();
	UFUNCTION()
	void ReactToQuestCompleted(const UQuestComponent* QuestComponent);

	AInteractionCharacter* SpawnQuestGiver(const UQuestTemplate* QuestTemplate);

	float RandomizeQuestSpawnInterval() const
	{
		if (ensure(QuestSpawnInterval > QuestSpawnDerivation))
		{
			return FMath::RandRange(QuestSpawnInterval - QuestSpawnDerivation,
									QuestSpawnInterval + QuestSpawnDerivation);
		}

		return QuestSpawnInterval;
	}

	virtual void BeginPlay() override;
};
