// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UniformGridPanel.h"
#include "AutoArrangedUniformGridPanel.generated.h"

/**
 * Uniform grid panel that automatically arranges children when added
 */
UCLASS()
class GENERICWIDGETS_API UAutoArrangedUniformGridPanel : public UUniformGridPanel
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
	int32 ColumnCount = 2;

	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
};
