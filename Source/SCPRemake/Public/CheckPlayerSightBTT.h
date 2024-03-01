// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <BehaviorTree/Tasks/BTTask_BlackboardBase.h>

#include "CheckPlayerSightBTT.generated.h"

UCLASS()
class SCPREMAKE_API UCheckPlayerSightBTT : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UCheckPlayerSightBTT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
