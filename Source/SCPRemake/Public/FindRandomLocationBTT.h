// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <BehaviorTree/Tasks/BTTask_BlackboardBase.h>

#include "FindRandomLocationBTT.generated.h"

UCLASS()
class SCPREMAKE_API UFindRandomLocationBTT : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindRandomLocationBTT();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	float SearchRadius = 3000.0f;
};
