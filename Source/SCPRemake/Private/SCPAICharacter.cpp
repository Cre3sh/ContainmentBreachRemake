// Fill out your copyright notice in the Description page of Project Settings.

#include "SCPAICharacter.h"

// Sets default values
ASCPAICharacter::ASCPAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASCPAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCPAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBehaviorTree* ASCPAICharacter::GetBehaviorTree() const
{
	return BehaviorTree;
}

