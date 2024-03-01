// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableObject.h"

#include <Components/WidgetComponent.h>

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetActorTickEnabled(false);
}

void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();

	HideInteractionWidget();
}

void AInteractableObject::Interact()
{
	// Overriden by derived classes to implement custom behaviour
}

void AInteractableObject::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);
}

void AInteractableObject::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}
