// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <GameFramework/Character.h>

#include "SCPAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SCPREMAKE_API ASCPAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCPAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree() const;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;
};
