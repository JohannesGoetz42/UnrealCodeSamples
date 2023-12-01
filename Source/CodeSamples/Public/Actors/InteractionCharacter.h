// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractionCharacter.generated.h"

UCLASS()
/**
 * Base class for characters the combat player can interact with
 */
class CODESAMPLES_API AInteractionCharacter : public ACharacter
{
	GENERATED_BODY()

	/** The implementation of the InteractionCharacter is out of the code sample's scope and therefore commented out
	 
public:
	AInteractionCharacter();

protected:
	UPROPERTY(EditAnywhere)
	class UWorldMarkerComponent* WorldMarkerComponent;
	UPROPERTY(EditAnywhere)
	class USphereComponent* InteractionSphere;
	UPROPERTY(EditAnywhere)
	/** Animation that is played when a player enters the interaction area */ /*
	UAnimSequence* GreetingAnimation;
	UPROPERTY()
	class UInteractiveNPCAnimInstance* AnimInstance;

	UFUNCTION()
	virtual void OnPlayerEnteredRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
									  const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnPlayerLeftRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Inherited via IEnvironmentInteraction
	virtual FVector GetInteractionLocation() const override { return GetActorLocation() + FVector(0, 0, 130.0f); }
	virtual void Interact(class APlayerControllerBase* PlayerController) override;
	virtual FText GetInteractionHintText() const override;
	virtual UWorldMarkerComponent* GetWorldMarkerComponent() const override { return WorldMarkerComponent; }
	virtual EInteractionType GetInteractionType() const override { return EInteractionType::IT_Conversation; }

	virtual void BeginPlay() override;
	*/
};
