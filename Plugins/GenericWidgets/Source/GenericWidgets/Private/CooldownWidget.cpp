// Fill out your copyright notice in the Description page of Project Settings.


#include "CooldownWidget.h"

#include "Components/TextBlock.h"

void UCooldownWidget::StartCooldown(float CooldownDuration)
{
	StopAllAnimations();
	RemainingCooldown = CooldownDuration;
	const float PlaybackSpeed = 1.0f / CooldownDuration;
	PlayAnimation(CooldownAnimation, 0, 1, EUMGSequencePlayMode::Forward, PlaybackSpeed);
	if (CooldownText)
	{
		CooldownText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UCooldownWidget::FinishCooldown()
{
	if (RemainingCooldown == 0.0f)
	{
		return;
	}

	RemainingCooldown = 0.0f;
	if (CooldownText)
	{
		CooldownText->SetVisibility(ESlateVisibility::Collapsed);
	}

	StopAllAnimations();
	PlayAnimation(CooldownCompletedAnimation);
}

void UCooldownWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (RemainingCooldown == 0.0f)
	{
		return;
	}

	const float NewRemainingCooldown = RemainingCooldown - InDeltaTime;
	if (NewRemainingCooldown <= 0.0f)
	{
		FinishCooldown();
		return;
	}

	RemainingCooldown = NewRemainingCooldown;

	if (CooldownText)
	{
		FNumberFormattingOptions CooldownTextFormat;
		CooldownTextFormat.MaximumFractionalDigits = 1;
		CooldownText->SetText(FText::AsNumber(RemainingCooldown, &CooldownTextFormat));
	}
}

void UCooldownWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CooldownText)
	{
		CooldownText->SetVisibility(ESlateVisibility::Collapsed);
	}
}
