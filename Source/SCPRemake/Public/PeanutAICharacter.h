// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SCPAICharacter.h"

#include "PeanutAICharacter.generated.h"

class APlayerCharacter;

UCLASS()
class SCPREMAKE_API APeanutAICharacter : public ASCPAICharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:

	UPROPERTY()
	APlayerCharacter* CachedPlayerCharacter = nullptr;
};
