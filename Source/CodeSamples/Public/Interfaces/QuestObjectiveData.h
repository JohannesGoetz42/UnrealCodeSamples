// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestObjectiveData.generated.h"

USTRUCT(Blueprintable)
/**
 * Used by some quest objectives to decide where and how many actors to spawn
 */
struct FQuestObjectiveSpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	/** The amount of actors that should be spawned by the objective */
	int32 SpawnedAmount = 1;
	UPROPERTY(EditAnywhere)
	/** This can be used to specify a spawn location by tag (optional) */
	FName SpawnLocationTag = FName();
};

// This class does not need to be modified.
UINTERFACE()
class UQuestObjectiveData : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for quest objective data assets
 */
class CODESAMPLES_API IQuestObjectiveData
{
	GENERATED_BODY()

public:
	/** Specifies which class should be instanced by the QuestComponent when the quest is accepted */
	virtual TSubclassOf<UActorComponent> GetComponentClass() const = 0;
};
