// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"


class UQuestDataBase;
DECLARE_MULTICAST_DELEGATE_OneParam(FQuestDelegate, const class UQuestComponent*);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CODESAMPLES_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FQuestDelegate OnQuestCompleted;

	const FORCEINLINE UQuestDataBase* GetQuestData() const { return QuestData; }

protected:
	UPROPERTY(VisibleAnywhere)
	const UQuestDataBase* QuestData;


	/** The following code is out of the code sample's scope and therefore commented out
public:

	FORCEINLINE TArray<UQuestObjectiveBase*> GetObjectives() const { return Objectives; }
	FORCEINLINE UQuestGiverComponent* GetQuestGiver() const { return QuestGiver; }
	void AcceptQuest();
	void DeclineQuest();
	void InitializeData(const UQuestDataBase* Quest, class UQuestGiverComponent* QuestGiverComponent = nullptr);
	void CompleteObjective(class UQuestObjectiveBase* CompletedObjective,
						   const TArray<const AActor*>& ObjectiveActors = TArray<const AActor*>());
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UQuestObjectiveBase*> Objectives;
	UPROPERTY(VisibleAnywhere)
	TArray<const UComponentTrigger*> QuestTriggerInstances;
	UPROPERTY()
	UUIManager* UIManager;
	UPROPERTY()
	UQuestGiverComponent* QuestGiver;
	UPROPERTY()
	APlayerControllerBase* PlayerController;

	const IHasLocationMarker* RecentlyFinishedObjectiveLocation;
	FTimerHandle FollowUpQuestDelayTimer;

	UFUNCTION()
	void StartFollowUpQuest();

	void CompleteQuest();
	void ApplyQuestRewards() const;
	virtual void CloseNotification() override;
	void InitializeObjectives();
	void AddObjective(const UDataAsset* ObjectiveData);
	virtual void DestroyComponent(bool bPromoteChildren = false) override;

	// Inherited via ITriggerableComponent
	virtual void Update(UComponentTrigger* CausingTrigger) override;
	virtual TArray<TSubclassOf<UComponentTrigger>> GetTriggerTypes() override;
	*/
};
