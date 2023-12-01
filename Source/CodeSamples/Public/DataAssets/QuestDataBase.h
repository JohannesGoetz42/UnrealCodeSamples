// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeSamples/Public/Interfaces/HasNotificationData.h"
#include "Engine/DataAsset.h"
#include "QuestDataBase.generated.h"

/**
* Struct for rewards
*/
USTRUCT(BlueprintType)
struct FPlayerRewardData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Coins = 0;

	/** The following properties are out of the code sample's scope and therefore commented out
	 
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<UTradeableItem>, uint32> Items = TMap<TSubclassOf<UTradeableItem>, uint32>();
	UPROPERTY(EditAnywhere)
	FResourceCollection Resources = FResourceCollection();
	UPROPERTY(EditAnywhere)
	FPopulationCollection Population = FPopulationCollection();
	UPROPERTY(EditAnywhere)
	TSet<TSubclassOf<ABuildingBase>> BuildingUnlocks = TSet<TSubclassOf<class ABuildingBase>>();
	UPROPERTY(EditAnywhere)
	TSet<TSubclassOf<ABuildingModuleBase>> UnlockedBuildingModules = TSet<TSubclassOf<ABuildingModuleBase>>();
	UPROPERTY(EditAnywhere)
	TSet<TSubclassOf<UProductionRecipeData>> UnlockedProductionRecipes = TSet<TSubclassOf<UProductionRecipeData>>();
	*/
};

/**
 * Base class for quests
 */
UCLASS()
class CODESAMPLES_API UQuestDataBase : public UDataAsset, public IHasNotificationData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FText QuestName;
	UPROPERTY(EditDefaultsOnly, meta = (MultiLine = "true"))
	TArray<FText> QuestTexts;
	UPROPERTY(EditDefaultsOnly, meta = (Category = "Rewards"))
	FPlayerRewardData Reward;
	UPROPERTY(EditDefaultsOnly, Instanced,
		meta = (MustImplement = "/Script/BootyIsland.QuestObjectiveData", Category = "Objective"))
	TArray<UDataAsset*> QuestObjectives;

	// Inherited via IHasNotificationData
	virtual TArray<FText> GetMessages() const override { return QuestTexts; }
	virtual FText GetHeadline() const override { return QuestName; }
};
