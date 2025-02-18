// Fill out your copyright notice in the Description page of Project Settings.


#include "Assembler.h"

#include "Assembler.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"

// Called when the game starts
void UAssembler::BeginPlay()
{
	Super::BeginPlay();

	// Setup overlap callbacks. 

}

void UAssembler::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ToDo: When the pinDock mesh on the wheel overlaps the pinDock mesh on the rotor, reparent "dock" the wheel
	// to the rotor.

}

void UAssembler::Focus(USelector* cursor, bool state)
{
	// Optional: Change some property of the clients material to highlight when focused. 
}

void UAssembler::ForePinch(USelector* selector, bool state)
{
	UGrabber::ForePinch(selector, state);


	// ToDo: Use inherited Grabber functionality when in normal grabbing mode.
	// Add snap and rotation functionailty when snapped.
}

void UAssembler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UGrabber::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// ToDo: Move the wheel as a UGrabber when undocked.
	// Rotate the wheel on the rotor when docked.
	// Undock the wheel when significant stress is placed on the rotor-wheel joint.

}
