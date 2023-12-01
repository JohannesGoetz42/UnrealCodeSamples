// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasLocationMarker.generated.h"

UENUM()
enum ELocationType
{
	LT_Any UMETA(DispayName = "Any"),
	LT_Transport UMETA(DispayName = "Transport"),
	LT_NPC UMETA(DispayName = "NPC"),
	LT_EnvironmentInteraction UMETA(DispayName = "Environment interaction"),
	LT_ChildActorSpawnLocation UMETA(DisplayName = "ChildActor SpawnLocation")
};

class ULocationMarkerComponent;

// This class does not need to be modified.
UINTERFACE()
class UHasLocationMarker : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for objects that have locations for specific uses
 */
class CODESAMPLES_API IHasLocationMarker
{
	GENERATED_BODY()

public:
	virtual void GetLocations(TArray<const ULocationMarkerComponent*>& OutLocations, ELocationType LocationType,
	                          FName LocationTag = FName()) const = 0;
	const ULocationMarkerComponent* GetClosest(const FVector& Destination, ELocationType LocationType,
	                                           FName LocationTag = FName()) const;
	const ULocationMarkerComponent* GetRandom(ELocationType LocationType, FName LocationTag = FName()) const;
};
