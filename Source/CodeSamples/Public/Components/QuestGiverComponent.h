// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestGiverComponent.generated.h"


class UQuestDataBase;

/**
 * Component for actors that can give a quest
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CODESAMPLES_API UQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void SetQuest(const UQuestDataBase* NewQuest);

protected:
	UPROPERTY(EditAnywhere)
	TArray<const UQuestDataBase*> AvailableQuests;

	/** The following code is out of the code sample's scope and therefore commented out
	  
public:
	void OnQuestAccepted(UQuestComponent* AcceptedQuest);

protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UQuestData>> StoryQuests;

	//Inherited via UInteractiveComponent
	virtual EInteractionType GetInteractionType() const override { return EInteractionType::IT_Conversation; }
	virtual void Interact(APlayerControllerBase* PlayerController) override;
	virtual bool IsInteractionAvailable() const override { return AvailableQuests.Num() > 0; }
	virtual void OnPlayerLeftRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual FText GetInteractionHintText() const override { return FText::FromString("View Quest"); }
	virtual void BeginPlay() override;
	*/
};
