// Fill out your copyright notice in the Description page of Project Settings.

#include "SCPAIController.h"

#include <BehaviorTree/BehaviorTree.h>

#include "SCPAICharacter.h"

ASCPAIController::ASCPAIController()
{
	
}

void ASCPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const ASCPAICharacter* const AICharacter = Cast<ASCPAICharacter>(InPawn);
	if (IsValid(AICharacter))
	{
		UBehaviorTree* const BehaviorTree = AICharacter->GetBehaviorTree();
		if (IsValid(BehaviorTree))
		{
			UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

			// Set our Blackboard Component
			UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);

			RunBehaviorTree(BehaviorTree);
		}
	}
}
