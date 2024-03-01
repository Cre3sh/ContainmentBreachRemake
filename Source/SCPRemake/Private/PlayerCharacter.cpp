// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include <Components/BoxComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/AudioComponent.h>

#include "DrawDebugHelpers.h"
#include "InteractableObject.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	FootStepAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	FootStepAudioComponent->SetupAttachment(RootComponent);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = PlayerWalkSpeed;

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnBoxEndOverlap);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovementState();
	UpdateCamera();
	UpdateFootsteps(DeltaTime);
}

bool APlayerCharacter::CheckLineOfSightWithPawn(const APawn* const Pawn) const
{
	const USkeletalMeshComponent* const SkeletalMeshComponent = Pawn->GetComponentByClass<USkeletalMeshComponent>();
	if (!IsValid(SkeletalMeshComponent))
	{
		return false;
	}

	const bool bWasComponentRendered = Pawn->WasRecentlyRendered() && SkeletalMeshComponent->GetLastRenderTimeOnScreen() == SkeletalMeshComponent->GetLastRenderTime();
	
    return bWasComponentRendered;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	InputComponent->BindAxis(TEXT("HoriMove"), this, &APlayerCharacter::HoriMove);
	InputComponent->BindAxis(TEXT("VertMove"), this, &APlayerCharacter::VertMove);

	InputComponent->BindAxis(TEXT("HoriRot"), this, &APlayerCharacter::HoriRot);
	InputComponent->BindAxis(TEXT("VertRot"), this, &APlayerCharacter::VertRot);

	InputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::UpdateMovementState()
{
	if (GetVelocity().Size() > 0.0f)
	{
		CurrentPlayerMovementState = Walking;

		return;
	}

	CurrentPlayerMovementState = Idle;
}

void APlayerCharacter::UpdateCamera()
{
	const APlayerController* const PlayerController = Cast<APlayerController>(GetController());

	check(PlayerController);

	PlayerController->PlayerCameraManager->StartCameraShake(*CameraShakes.Find(CurrentPlayerMovementState));
}

void APlayerCharacter::UpdateFootsteps(const float DeltaTime)
{
	DistanceTravelled += GetVelocity().Size() * DeltaTime;

	if (!(DistanceTravelled >= 200.0f))
	{
		return;
	}

	const int32 RandIndex = FMath::RandRange(0, ConcreteFootsteps.Num() - 1);
	switch (CurrentPlayerMovementState)
	{
		case Walking:
			if (!ConcreteFootsteps.IsValidIndex(RandIndex))
			{
				return;
			}

			FootStepAudioComponent->SetSound(ConcreteFootsteps[RandIndex]);
			FootStepAudioComponent->Play();
			DistanceTravelled = 0.0f;

			break;

		case Running:
			break;

		case Idle:
			break;
		
	}
}

void APlayerCharacter::Interact()
{
	if (CurrentInteractingObject.IsValid())
	{
		CurrentInteractingObject->Interact();
	}
}

bool APlayerCharacter::TraceAgainstEdgeOfScreen(const AActor* const Actor)
{
	// Get player controller
	APlayerController* const PlayerController = GetWorld()->GetFirstPlayerController();

	// Get viewport size
	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Calculate the screen coordinates for the leftmost part of the viewport
	FVector2D LeftmostViewportPoint(0, ViewportSizeY / 2); // Assuming Y is the horizontal axis
	
	// Convert screen coordinates to world location
	FVector LeftmostWorldPoint;
	FVector LeftWorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(LeftmostViewportPoint.X, LeftmostViewportPoint.Y, LeftmostWorldPoint, LeftWorldDirection);

	LeftWorldDirection *= 1000.0f;

	FCollisionQueryParams QueryParams;

	QueryParams.AddIgnoredActor(this);
	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, LeftmostWorldPoint, Actor->GetActorLocation(), ECC_Visibility, QueryParams);
	DrawDebugLine(GetWorld(), LeftmostWorldPoint, LeftWorldDirection, FColor::Red, false, 0.1f);

	if (Hit.GetActor() == Actor)
	{
		return true;
	}

	return false;
}

void APlayerCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const UWorld* const World = GetWorld();

	check(World);

	if (!IsValid(OtherActor))
	{
		return;
	}

	FHitResult HitResult;

	World->LineTraceSingleByChannel(HitResult, GetActorLocation(), OtherActor->GetActorLocation(), ECC_Visibility);
	
	AActor* const ActorHit = HitResult.GetActor();
	if (!IsValid(ActorHit))
	{
		return;
	}

	AInteractableObject* const HitInteractable = Cast<AInteractableObject>(ActorHit);
	if (IsValid(HitInteractable))
	{
		// We can only interact with one object at a time
		if (CurrentInteractingObject.IsValid())
		{
			CurrentInteractingObject->HideInteractionWidget();
		}

		CurrentInteractingObject = HitInteractable;
		CurrentInteractingObject->ShowInteractionWidget();
	}
}

void APlayerCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const AInteractableObject* const InteractableObject = Cast<AInteractableObject>(OtherActor);
	if (InteractableObject == CurrentInteractingObject)
	{
		if (CurrentInteractingObject.IsValid())
		{
			CurrentInteractingObject->HideInteractionWidget();
			CurrentInteractingObject.Reset();
		}
	}
}

void APlayerCharacter::HoriMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void APlayerCharacter::VertMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);

	}
}

void APlayerCharacter::HoriRot(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void APlayerCharacter::VertRot(float value)
{
	if (value)
	{
		/*Clamp the camera's rotation*/
		float temp = Camera->GetRelativeRotation().Pitch + value;

		if (temp < 65 && temp > -65)
		{
			Camera->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

