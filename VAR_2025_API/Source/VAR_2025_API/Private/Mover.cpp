// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMover::MoveUpDown(const float percentage)
{
	UE_LOG(LogTemp, Warning, TEXT("UpDown:%f"), percentage);

	float newZ = percentage * 100.0f;
	FVector newLocation = GetRelativeLocation();
	newLocation.Z = newZ;
	SetRelativeLocation(newLocation);

}

void UMover::Rotate(const float degrees)
{
	UE_LOG(LogTemp, Warning, TEXT("Rotate:%f"), degrees);
	FQuat newRotation = FQuat(FVector::UpVector, FMath::DegreesToRadians(degrees));
	SetRelativeRotation(newRotation);
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

