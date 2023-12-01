// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasNotificationData.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHasNotificationData : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for objects that have data displayed in a notification widget
 */
class CODESAMPLES_API IHasNotificationData
{
	GENERATED_BODY()
	
public:
	virtual FText GetHeadline() const = 0;
	virtual TArray<FText> GetMessages() const = 0;
};
