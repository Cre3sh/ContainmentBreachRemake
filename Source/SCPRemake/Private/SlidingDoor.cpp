// Fill out your copyright notice in the Description page of Project Settings.

#include "SlidingDoor.h"

#include <Components/AudioComponent.h>

#include "ButtonPanel.h"

// Sets default values
ASlidingDoor::ASlidingDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = Root;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));

	FrontButtonHolder = CreateDefaultSubobject<USceneComponent>(TEXT("Front Button Holder"));
	BackButtonHolder = CreateDefaultSubobject<USceneComponent>(TEXT("Back Button Holder"));

	FrontDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Door"));
	FrontDoor->SetupAttachment(RootComponent);
	
	BackDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Back Door"));
	BackDoor->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();

	FrontDoorClosedLocation = FrontDoor->GetRelativeLocation();
	FrontDoorOpenedLocation = -FrontDoor->GetRelativeTransform().GetUnitAxis(EAxis::X) * SlideDistance;

	BackDoorClosedLocation = BackDoor->GetRelativeLocation();
	BackDoorOpenedLocation = -BackDoor->GetRelativeTransform().GetUnitAxis(EAxis::X) * SlideDistance;

	UWorld* const World = GetWorld();

	check(World);

	// Instantiate buttons
	FrontButtonPanel = Cast<AButtonPanel>(World->SpawnActor(ButtonClass, &GetActorTransform()));
	BackButtonPanel = Cast<AButtonPanel>(World->SpawnActor(ButtonClass, &GetActorTransform()));

	check(FrontButtonPanel);

	FrontButtonPanel->AttachToComponent(FrontButtonHolder, FAttachmentTransformRules::SnapToTargetIncludingScale);

	FrontButtonPanel->OnButtonPanelPressed.AddDynamic(this, &ASlidingDoor::ButtonPressed);

	check(BackButtonPanel);

	BackButtonPanel->AttachToComponent(BackButtonHolder, FAttachmentTransformRules::SnapToTargetIncludingScale);

	BackButtonPanel->OnButtonPanelPressed.AddDynamic(this, &ASlidingDoor::ButtonPressed);
}

// Called every frame
void ASlidingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentState != DesiredState)
	{
		switch (DesiredState)
		{
			case Open:
				FrontDoor->SetRelativeLocation(FMath::VInterpConstantTo(FrontDoor->GetRelativeLocation(), FrontDoorOpenedLocation, DeltaTime, SlideSpeed));
				BackDoor->SetRelativeLocation(FMath::VInterpConstantTo(BackDoor->GetRelativeLocation(), BackDoorOpenedLocation, DeltaTime, SlideSpeed));

				if (FrontDoor->GetRelativeLocation().Equals(FrontDoorOpenedLocation, 0.2f) || BackDoor->GetRelativeLocation().Equals(BackDoorOpenedLocation))
				{
					FrontDoor->SetRelativeLocation(FrontDoorOpenedLocation);
					BackDoor->SetRelativeLocation(BackDoorOpenedLocation);

					FrontButtonPanel->ChangeState(Usable);
					BackButtonPanel->ChangeState(Usable);

					CurrentState = DesiredState;
				}

				break;

			case Closed:

				FrontDoor->SetRelativeLocation(FMath::VInterpConstantTo(FrontDoor->GetRelativeLocation(), FrontDoorClosedLocation, DeltaTime, SlideSpeed));
				BackDoor->SetRelativeLocation(FMath::VInterpConstantTo(BackDoor->GetRelativeLocation(), BackDoorClosedLocation, DeltaTime, SlideSpeed));

				if (FrontDoor->GetRelativeLocation().Equals(FrontDoorClosedLocation, 0.2f) || BackDoor->GetRelativeLocation().Equals(BackDoorClosedLocation))
				{
					FrontDoor->SetRelativeLocation(FrontDoorClosedLocation);
					BackDoor->SetRelativeLocation(BackDoorClosedLocation);

					FrontButtonPanel->ChangeState(Usable);
					BackButtonPanel->ChangeState(Usable);

					CurrentState = DesiredState;
				}

				break;
		}
	}
}

void ASlidingDoor::ButtonPressed()
{
	if (DesiredState == CurrentState)
	{
		switch (CurrentState)
		{
			case Closed:
				DesiredState = Open;

				FrontButtonPanel->ChangeState(Occupied);
				BackButtonPanel->ChangeState(Occupied);
				break;
			case Open:
				DesiredState = Closed;

				FrontButtonPanel->ChangeState(Occupied);
				BackButtonPanel->ChangeState(Occupied);
				break;
		}
	}
}

