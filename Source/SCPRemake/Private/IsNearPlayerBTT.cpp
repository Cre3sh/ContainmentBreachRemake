// Fill out your copyright notice in the Description page of Project Settings.

#include "IsNearPlayerBTT.h"

#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <AIController.h>

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UIsNearPlayerBTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = nullptr;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	ACharacter* const PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!IsValid(PlayerCharacter))
	{
		return EBTNodeResult::Failed;
	}

	AAIController* const AIController = OwnerComp.GetAIOwner();
	if (!IsValid(AIController))
	{
		return EBTNodeResult::Failed; 
	}

	const APawn* const AIPawn = AIController->GetPawn();
	if (!IsValid(AIPawn))
	{
		return EBTNodeResult::Failed;
	}

	if (float Distance = FVector::Dist(AIPawn->GetActorLocation(), PlayerCharacter->GetActorLocation()) <= 25000.0f)
	{
		BlackboardComponent->SetValueAsObject("PlayerActor", PlayerCharacter);
		BlackboardComponent->SetValueAsFloat(GetSelectedBlackboardKey(), Distance);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}