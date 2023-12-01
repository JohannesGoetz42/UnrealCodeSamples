// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TradeableItem.generated.h"

/**
 * Base class for items that can be traded
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class CODESAMPLES_API UTradeableItem : public UDataAsset
{
	GENERATED_BODY()

public:
	/** The following code is out of the code sample's scope and therefore commented out
	 
	UFUNCTION(BlueprintCallable)
	virtual int32 GetBasePrice() const { return BasePrice; }

	UFUNCTION(BlueprintCallable)
	virtual UTexture2D* GetThumbnail() const { return Thumbnail; }

	UFUNCTION(BlueprintCallable)
	virtual FText GetItemName() const { return Name; }

	UFUNCTION(BlueprintCallable)
	virtual EItemRarity GetItemRarity() const { return Rarity; }

	UFUNCTION(BlueprintCallable)
	virtual TArray<EItemAction> GetAvailableActions() const
	{
		return TArray<EItemAction>();
	}

	UFUNCTION(BlueprintCallable)
	virtual EItemAction GetDefaultAction() const { return EItemAction::IA_None; }

	UFUNCTION(BlueprintCallable)
	virtual TSubclassOf<UTradeableItemDetailWidget> GetDetailWidgetClass() const { return DetailWidgetClass; }

	virtual FText GetHelpText(const APlayerController* PlayerController) const { return FText(); }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Category = "GUI"))
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Category = "GUI"))
	UTexture2D* Thumbnail;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Category = "GUI"))
	TSubclassOf<UTradeableItemDetailWidget> DetailWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Category = "Trade"))
	int32 BasePrice = 9001; // its over 9000!!!
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Category = "Trade"))
	EItemRarity Rarity = EItemRarity::IR_Common;
	*/
};
