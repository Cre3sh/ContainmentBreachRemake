// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <AIController.h>

#include "SCPAIController.generated.h"

UCLASS()
class SCPREMAKE_API ASCPAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASCPAIController();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
