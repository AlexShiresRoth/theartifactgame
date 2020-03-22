// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldPosition.h"
#include "GameFramework/Actor.h"
// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	//Getting the player location
	FString PlayerLocation = GetOwner()->GetActorLocation().ToString();

	FString PlayerLog = GetOwner()->GetName();

	UE_LOG(LogTemp, Warning, TEXT("Controlling %s"), *PlayerLog);

	UE_LOG(LogTemp, Warning, TEXT("Player at %s"), *PlayerLocation);
}

// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
