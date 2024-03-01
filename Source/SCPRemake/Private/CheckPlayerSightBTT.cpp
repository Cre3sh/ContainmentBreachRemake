// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckPlayerSightBTT.h"

#include <Kismet/GameplayStatics.h>
#include <AIController.h>
#include <PlayerCharacter.h>
#include <BehaviorTree/BlackboardComponent.h>

UCheckPlayerSightBTT::UCheckPlayerSightBTT()
{
	NodeName = "Check Player Line of Sight";
}

EBTNodeResult::Type UCheckPlayerSightBTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = nullptr;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	APlayerCharacter* const PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
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

	if(PlayerCharacter->CheckLineOfSightWithPawn(AIPawn))
	{
		BlackboardComponent->SetValueAsBool(GetSelectedBlackboardKey(), true);
		AIController->StopMovement();

		return EBTNodeResult::Succeeded;
	}

	BlackboardComponent->SetValueAsBool(GetSelectedBlackboardKey(), false);
	return EBTNodeResult::Failed;
}
