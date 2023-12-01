// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeSamples/Public/Components/QuestGiverComponent.h"

void UQuestGiverComponent::SetQuest(const UQuestDataBase* NewQuest)
{
	ensure(NewQuest);
	AvailableQuests.Add(NewQuest);

	/** The following code is out of the code sample's scope and therefore commented out

	const IEnvironmentInteraction* InteractionActor = Cast<IEnvironmentInteraction>(GetOwner());
	if (UWorldMarkerComponent* WorldMarker = InteractionActor->GetWorldMarkerComponent())
	{
		WorldMarker->SetMarkerState(EWorldMarkerState::WMS_Active);
	}
	*/
}
