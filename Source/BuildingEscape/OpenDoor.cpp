// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialZed = GetOwner()->GetActorLocation().Z;
	CurrentZed = InitialZed;
	TargetZed = CurrentZed - TargetZed;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has door component but no pressure plate selected!!!!!!!!!!!!!!!!!!!!!"), *GetOwner()->GetName());
	}

	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FVector CurrentLocation = GetOwner()->GetActorLocation();

	FVector OpenDoor(CurrentLocation.X, CurrentLocation.Y, CurrentZed);

	CurrentZed = FMath::FInterpTo(CurrentZed, TargetZed, DeltaTime, 2);

	GetOwner()->SetActorLocation(OpenDoor);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FVector InitialLocation = GetOwner()->GetActorLocation();

	FVector CloseDoor(InitialLocation.X, InitialLocation.Y, CurrentZed);

	CurrentZed = FMath::FInterpTo(CurrentZed, InitialZed, DeltaTime, 2);

	GetOwner()->SetActorLocation(CloseDoor);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		DoorLastOpen = GetWorld()->GetTimeSeconds();
		OpenDoor(DeltaTime);
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpen > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}
