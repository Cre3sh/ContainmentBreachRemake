// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Actor.h>

#include "SlidingDoor.generated.h"

class UPointLightComponent;
class AButtonPanel;

UENUM()
enum EDoorState
{
	Open,
	Closed
};

UCLASS()
class SCPREMAKE_API ASlidingDoor : public AActor
{
	GENERATED_BODY()
	
private:
	UFUNCTION()
	void ButtonPressed();
	
	// Sets default values for this actor's properties
	ASlidingDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> AudioComponent = nullptr;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> FrontButtonHolder = nullptr;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> BackButtonHolder = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> FrontDoorOpenedHolder = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> BackDoorOpenedHolder = nullptr;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> FrontDoor = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> BackDoor = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AButtonPanel> ButtonClass = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AButtonPanel> FrontButtonPanel = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AButtonPanel> BackButtonPanel = nullptr;

	UPROPERTY(EditAnywhere)
	FTransform FrontButtonOffset = FTransform(FRotator(0,0,0), FVector(-12.0f,122.0f,142.0f));

	UPROPERTY(EditAnywhere)
	FTransform BackButtonOffset = FTransform(FRotator(0,0,-180), FVector(35.0f,-129.0f,142.0f));

	UPROPERTY(EditAnywhere)
	float SlideDistance = 120.0f;

	UPROPERTY(EditAnywhere)
	float SlideSpeed = 75.0f;

	FVector FrontDoorClosedLocation = FVector::ZeroVector;
	FVector FrontDoorOpenedLocation = FVector::ZeroVector;

	FVector BackDoorClosedLocation = FVector::ZeroVector;
	FVector BackDoorOpenedLocation = FVector::ZeroVector;

	EDoorState CurrentState = Closed;

	EDoorState DesiredState = Closed;
};