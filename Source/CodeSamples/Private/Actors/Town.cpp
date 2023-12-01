#include "CodeSamples/Public/Actors/Town.h"

#include "CodeSamples/Public/Components/QuestGenerator.h"
#include "CodeSamples/Public/Interfaces/HasLocationMarker.h"
#include "Components/SphereComponent.h"

ATown::ATown() : Super()
{
	USphereComponent* Sphere = CreateDefaultSubobject<USphereComponent>(FName("Root Component"));
	Sphere->ShapeColor = FColor::Orange;
	RootComponent = Sphere;

	QuestGenerator = CreateDefaultSubobject<UQuestGenerator>(FName("Quest Generator"));

	/** The following code is out of the code sample's scope and therefore commented out

	CivilianSpawner = CreateDefaultSubobject<UCivilianSpawnerComponent>(FName("Civilian Spawner"));
	PopulationManager = CreateDefaultSubobject<UPopulationManager>(FName("Population Manager"));
	HappinessManager = CreateDefaultSubobject<UHappinessManager>(FName("Happiness Manager"));
	ResourceManager = CreateDefaultSubobject<UResourceManager>(FName("Resource Manager"));
	QuestGenerator = CreateDefaultSubobject<UQuestGenerator>(FName("Quest Generator"));
	ConsumptionManager = CreateDefaultSubobject<UConsumptionManager>(FName("Consumption Manager"));
	AreaEffectManager = CreateDefaultSubobject<UAreaEffectManager>(FName("Area effect manager"));
	*/
}

void ATown::GetLocationSources(TSubclassOf<UObject> ObjectType,
                               TSet<const IHasLocationMarker*>& OutLocationSources) const
{
	return;

	/** The implementation is commented out, since the types are not known in the code sample

	if (const TSubclassOf<ABuildingBase> BuildingType{ObjectType})
	{
		for (const ABuildingBase* BuildingInstance : GetBuildingInstances(BuildingType))
		{
			OutLocationSources.Add(Cast<IHasLocationMarker>(BuildingInstance));
		}

		return;
	}
	if (const TSubclassOf<ABuildingModuleBase> BuildingModuleType{ObjectType})
	{
		for (const ABuildingModuleBase* BuildingModuleInstance : GetBuildingModuleInstances(BuildingModuleType))
		{
			OutLocationSources.Add(Cast<IHasLocationMarker>(BuildingModuleInstance));
		}

		return;
	}

	checkNoEntry(); // implement cache and retrieval for the object type!
	*/
}
