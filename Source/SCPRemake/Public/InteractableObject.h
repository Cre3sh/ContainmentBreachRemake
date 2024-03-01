// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

class UWidgetComponent;

UCLASS()
class SCPREMAKE_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

	// Begin AActor override
	virtual void BeginPlay() override;
	// End AActor override

	// Overriden by derived classes to implement custom behaviour
	virtual void Interact();

	virtual void ShowInteractionWidget();
	virtual void HideInteractionWidget();

protected:
	UPROPERTY(EditAnywhere)
	UWidgetComponent* InteractionWidget = nullptr;
};
