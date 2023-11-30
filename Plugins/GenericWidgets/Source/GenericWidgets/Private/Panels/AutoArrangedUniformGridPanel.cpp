// Fill out your copyright notice in the Description page of Project Settings.


#include "Panels/AutoArrangedUniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UAutoArrangedUniformGridPanel::OnSlotAdded(UPanelSlot* InSlot)
{
	const int32 SlotIndex = GetChildrenCount() - 1;
	const int32 RowIndex = FMath::Floor(SlotIndex / ColumnCount);
	const int32 ColumnIndex = SlotIndex % ColumnCount;

	UUniformGridSlot* UniformGridSlot = Cast<UUniformGridSlot>(InSlot);
	UniformGridSlot->SetRow(RowIndex);
	UniformGridSlot->SetColumn(ColumnIndex);

	Super::OnSlotAdded(InSlot);
}
