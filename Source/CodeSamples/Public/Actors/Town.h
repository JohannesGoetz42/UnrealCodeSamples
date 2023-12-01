// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Town.generated.h"

class IHasLocationMarker;

UCLASS()
class CODESAMPLES_API ATown : public AActor
{
	GENERATED_BODY()

public:
	ATown();
	
	void GetLocationSources(TSubclassOf<UObject> ObjectType, TSet<const IHasLocationMarker*>& OutLocationSources) const;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UQuestGenerator* GetQuestGenerator() const { return QuestGenerator; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Generator")
	UQuestGenerator* QuestGenerator;

	/** The following code is out of the code sample's scope and therefore commented out
public:

	static void GetAllTowns(const UWorld* World, TArray<ATown*>& OutTowns);
	static void GetAllTowns(const UWorld* World, TArray<const ATown*>& OutTowns);
	static ATown* GetTownAtLocation(const UWorld* World, FVector Location);

	 
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UPopulationManager* GetPopulationManager() const { return PopulationManager; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class UHappinessManager* GetHappinessManager() const { return HappinessManager; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE class UResourceManager* GetResourceManager() const { return ResourceManager; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UConsumptionManager* GetConsumptionManager() const { return ConsumptionManager; }

	FORCEINLINE UAreaEffectManager* GetAreaEffectManager() const { return AreaEffectManager; }

	UFUNCTION(BlueprintCallable)
	TSet<ABuildingBase*> GetBuildingInstances(TSubclassOf<ABuildingBase> BuildingType) const
	{
		return Buildings.FindRef(BuildingType).Instances;
	}

	TSet<ABuildingModuleBase*> GetBuildingModuleInstances(TSubclassOf<ABuildingModuleBase> ModuleType) const
	{
		return BuildingModules.FindRef(ModuleType).Instances;
	}

	void RegisterBuilding(ABuildingBase* Building);
	void UnregisterBuilding(const ABuildingBase* Building);
	void RegisterBuildingModule(ABuildingModuleBase* BuildingModule);
	void UnRegisterBuildingModule(const ABuildingModuleBase* BuildingModule);

	const TMap<FName, UStaticMesh*>& GetCharacterAttachments() const
	{
		return CharacterAttachments;
	}

	// Inherited via IHasResourceStorage
	virtual UResourceStorageComponent* GetStorage() const override;

protected:
	UPROPERTY()
	TMap<TSubclassOf<ABuildingBase>, FBuildingInstanceData> Buildings;
	UPROPERTY()
	TMap<TSubclassOf<ABuildingModuleBase>, FBuildingModuleInstanceData> BuildingModules;
	UPROPERTY()
	UAreaEffectManager* AreaEffectManager;
	UPROPERTY(EditAnywhere)
	UPopulationManager* PopulationManager;
	UPROPERTY(EditAnywhere)
	UHappinessManager* HappinessManager;
	UPROPERTY(EditAnywhere)
	UResourceManager* ResourceManager;
	UPROPERTY(EditAnywhere)
	class UCivilianSpawnerComponent* CivilianSpawner;
	UPROPERTY(EditAnywhere)
	UConsumptionManager* ConsumptionManager;
	UPROPERTY(EditAnywhere, Category = "Cosmetic")
	TMap<FName, UStaticMesh*> CharacterAttachments;
	*/
};
