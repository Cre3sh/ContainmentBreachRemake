// Fill out your copyright notice in the Description page of Project Settings.

#include "FindRandomLocationBTT.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <NavigationSystem.h>

#include "SCPAIController.h"

UFindRandomLocationBTT::UFindRandomLocationBTT()
{
	NodeName = "FindRandomLocation";
}

EBTNodeResult::Type UFindRandomLocationBTT::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const ASCPAIController* const AIController = Cast<ASCPAIController>(OwnerComp.GetAIOwner());
	if (IsValid(AIController))
	{
		const APawn* const AIPawn = AIController->GetPawn();
		if (IsValid(AIPawn))
		{
			const FVector& Origin = AIPawn->GetActorLocation();

			const UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
			if (IsValid(NavigationSystem))
			{
				FNavLocation NavLocation;
				if(NavigationSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, NavLocation))
				{
					UBlackboardComponent* BlackboardComponent = nullptr;
					BlackboardComponent = OwnerComp.GetBlackboardComponent();
					if (IsValid(BlackboardComponent))
					{
						BlackboardComponent->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
					
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
