// Fill out your copyright notice in the Description page of Project Settings.

#include "PeanutAICharacter.h"

#include <Kismet/GameplayStatics.h>
#include <PlayerCharacter.h>

void APeanutAICharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerCharacter* const PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(PlayerCharacter))
	{
		return;
	}

	CachedPlayerCharacter = PlayerCharacter;
}

void APeanutAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!IsValid(CachedPlayerCharacter))
	{
		return;
	}

	/*We want to check line of sight here because AIMoveTo doesn't run in parallel and so doesn't reevaluate conditions when running
	 * and I can't be bothered to make a new BT task to move with so i'm just going to hack around the issue, thanks Unreal.
	 */
	if(CachedPlayerCharacter->CheckLineOfSightWithPawn(this))
	{
		GetController()->StopMovement();
	}
}
