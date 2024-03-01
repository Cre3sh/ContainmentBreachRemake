// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Character.h>

#include "PlayerCharacter.generated.h"

class UPawnSensingComponent;
class AInteractableObject;
class UBoxComponent;
class UCameraComponent;

UENUM()
enum EMovementState
{
	Idle,
	Walking,
	Running
};

UCLASS()
class SCPREMAKE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CheckLineOfSightWithPawn(const APawn* const Pawn) const;

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateMovementState();
	void UpdateCamera();
	void UpdateFootsteps(float DeltaTime);

	void Interact();

	bool TraceAgainstEdgeOfScreen(const AActor* const Actor);

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void HoriMove(float value);

	void VertMove(float value);

	void HoriRot(float value);

	void VertRot(float value);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> Camera = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAudioComponent> FootStepAudioComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> InteractionBox = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<EMovementState>, TSubclassOf<UCameraShakeBase>> CameraShakes;

	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<USoundBase>> ConcreteFootsteps;
	
	UPROPERTY(EditDefaultsOnly)
	float PlayerWalkSpeed = 250.0f;
	
	TWeakObjectPtr<AInteractableObject> CurrentInteractingObject = nullptr;
	
	EMovementState CurrentPlayerMovementState;

	float DistanceTravelled = 0.0f;
};