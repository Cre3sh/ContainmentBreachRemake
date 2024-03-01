// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableObject.h"

#include "ButtonPanel.generated.h"

class UPointLightComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPanelPressed);

UENUM()
enum EButtonState
{
	Usable,
	Occupied,
	Locked
};

UCLASS()
class SCPREMAKE_API AButtonPanel : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	AButtonPanel();

	virtual void BeginPlay() override;
	
	virtual void Interact() override;

	void ChangeState(EButtonState NewState);

	FOnButtonPanelPressed OnButtonPanelPressed;

	EButtonState CurrentState;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPointLightComponent> PointLightComponent = nullptr;
};
