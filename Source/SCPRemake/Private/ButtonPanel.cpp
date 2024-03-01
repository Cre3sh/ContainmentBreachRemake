// Fill out your copyright notice in the Description page of Project Settings.

#include "ButtonPanel.h"

#include <Components/PointLightComponent.h>
#include <Components/WidgetComponent.h>

AButtonPanel::AButtonPanel()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(StaticMeshComponent);
}

void AButtonPanel::BeginPlay()
{
	Super::BeginPlay();

	PointLightComponent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	PointLightComponent->AddLocalOffset(FVector(0.0f, 0.0f, -10.0f) + PointLightComponent->GetRelativeTransform().GetUnitAxis(EAxis::Y) * 50);
}

void AButtonPanel::Interact()
{
	if (CurrentState < 1 && OnButtonPanelPressed.IsBound())
	{
		OnButtonPanelPressed.Broadcast();
	}
}

void AButtonPanel::ChangeState(EButtonState NewState)
{
	CurrentState = NewState;

	switch (CurrentState)
	{
		case Usable:
			PointLightComponent->SetLightColor(FLinearColor::Green);
			break;

		case Occupied:
			PointLightComponent->SetLightColor(FLinearColor::Yellow);
			break;

		case Locked:
			PointLightComponent->SetLightColor(FLinearColor::Red);
			break;
	}
}
