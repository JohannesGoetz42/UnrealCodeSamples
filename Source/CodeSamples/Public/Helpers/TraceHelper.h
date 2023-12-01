// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define TRACE_LANDSCAPE ECollisionChannel::ECC_GameTraceChannel1

namespace TraceHelper
{
	/** 
	 * Sends a vertical trace from the location to find the landscape
	 * this can be used to place objects at the correct height
	 */ 
	inline bool GetLandscapeHitCloseToLocation(FHitResult& OutHit, UWorld* World, FVector Location, float TraceRange = 500.0f)
	{
		
		FVector TraceStart = Location + FVector(0, 0, TraceRange);
		FVector TraceEnd = Location + FVector(0, 0, -TraceRange);

		FHitResult Result;
		return World->LineTraceSingleByChannel(OutHit, TraceStart, TraceEnd, TRACE_LANDSCAPE);
	}
}
