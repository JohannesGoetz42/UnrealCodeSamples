// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodeSamples/Public/Interfaces/HasLocationMarker.h"
#include "Components/ArrowComponent.h"
#include "LocationMarkerComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CODESAMPLES_API ULocationMarkerComponent : public UArrowComponent
{
	GENERATED_BODY()

public:
	ULocationMarkerComponent();

	UFUNCTION(BlueprintCallable)
	const TArray<TEnumAsByte<ELocationType>>& GetTargetTypes() const { return TargetTypes; }

	UFUNCTION(BlueprintCallable)
	bool AcceptsType(ELocationType LocationType) const
	{
		return TargetTypes.Contains(LocationType) || TargetTypes.Contains(ELocationType::LT_Any);
	}

	void PlaceOnGround();

protected:
	UPROPERTY(EditAnywhere)
	/** The location types this marker can be used for */
	TArray<TEnumAsByte<ELocationType>> TargetTypes;
	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool bPlaceOnGround = true;

	virtual void BeginPlay() override;
};
