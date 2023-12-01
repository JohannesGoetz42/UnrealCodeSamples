// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CooldownWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * Base class for widgets that display a cooldown
 */
UCLASS(Abstract)
class GENERICWIDGETS_API UCooldownWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UImage* Thumbnail;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	/** The cooldown Animation. Should have a play length of 1 second, so the playback speed is calculated correctly */
	UWidgetAnimation* CooldownAnimation;
	UPROPERTY(meta = (BindWidgetOptional))
	/** Displays the remaining cooldown as a number */
	UTextBlock* CooldownText;
	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	/** Animation that is played when the cooldown is completed (i.E. a flash animation) */
	UWidgetAnimation* CooldownCompletedAnimation;

	float RemainingCooldown = 0.0f;

	void StartCooldown(float CooldownDuration);
	void FinishCooldown();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
};
