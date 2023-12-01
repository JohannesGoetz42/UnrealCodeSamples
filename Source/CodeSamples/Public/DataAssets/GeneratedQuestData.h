// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestDataBase.h"
#include "GeneratedQuestData.generated.h"

/**
 * Base class for generated quests that are generated at runtime based on the current state of the world
 */
UCLASS()
class CODESAMPLES_API UGeneratedQuestData : public UQuestDataBase
{
	GENERATED_BODY()

public:
	FTransform QuestGiverTransform;
};
