
#include "CodeSamples/Public/Interfaces/HasLocationMarker.h"

#include "CodeSamples/Public/Components/LocationMarkerComponent.h"

const ULocationMarkerComponent* IHasLocationMarker::GetClosest(const FVector& Destination, ELocationType LocationType,
                                                               FName LocationTag) const
{
	const ULocationMarkerComponent* Result = nullptr;
	TArray<const ULocationMarkerComponent*> AvailableLocations;
	GetLocations(AvailableLocations, LocationType, LocationTag);
	float ClosestDistSquared = FLT_MAX;
	for (const ULocationMarkerComponent* AvailableLocation : AvailableLocations)
	{
		const float CurrentDistSquared = (Destination - AvailableLocation->GetComponentLocation()).SizeSquared();
		if (CurrentDistSquared < ClosestDistSquared)
		{
			ClosestDistSquared = CurrentDistSquared;
			Result = AvailableLocation;
		}
	}

	return Result;
}

const ULocationMarkerComponent* IHasLocationMarker::GetRandom(ELocationType LocationType, FName LocationTag) const
{
	TArray<const ULocationMarkerComponent*> AvailableLocations;
	GetLocations(AvailableLocations, LocationType, LocationTag);
	if (AvailableLocations.IsEmpty())
	{
		checkNoEntry();
		return nullptr;
	}

	const int32 RandomIndex = FMath::RandRange(0, AvailableLocations.Num() - 1);
	if (const ULocationMarkerComponent* AvailableLocation = AvailableLocations[RandomIndex])
	{
		return AvailableLocation;
	}

	checkNoEntry();
	return nullptr;
}
