// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeSamples/Public/Components/LocationMarkerComponent.h"
#include "CodeSamples/Public/Helpers/TraceHelper.h"

ULocationMarkerComponent::ULocationMarkerComponent() : Super()
{
	bHiddenInGame = true;
	TargetTypes.Add(ELocationType::LT_Any);
}

void ULocationMarkerComponent::BeginPlay()
{
	Super::BeginPlay();
	PlaceOnGround();
}

void ULocationMarkerComponent::PlaceOnGround()
{
	if (bPlaceOnGround)
	{
		FHitResult LandscapeHit;
		if (TraceHelper::GetLandscapeHitCloseToLocation(LandscapeHit, GetWorld(), GetComponentLocation()))
		{
			SetWorldLocation(LandscapeHit.Location);
		}
	}
}
