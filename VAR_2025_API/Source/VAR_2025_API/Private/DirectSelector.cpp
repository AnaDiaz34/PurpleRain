// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectSelector.h"
#include "Vodget.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "MotionControllerComponent.h"

// Sets default values for this component's properties
UDirectSelector::UDirectSelector()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDirectSelector::BeginPlay()
{
	// ToDo: In the DirectPawn blueprint, add sphere components to the left and right controllers
	// and configure the sphere collision physics to send overlap events.

	// Next, in this method, cast the hands SceneComponent to UStaticMeshComponent and
	// add overlap begin and end callbacks to the child mesh.
	// Hint: An alternative method might be to set the mesh as a property and configure in the pawn.

}

void UDirectSelector::SetCursor()
{
	// Set the cursor FTransform to the world location of the controller.
}

void UDirectSelector::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Search for Vodget components even when focus is grabbed.
	// When focus is grabbed it is possible to exit our current focusVodget. If this occurs 
	// we keep track of the exit to allow focus to be lost when focus grab is released.

}

void UDirectSelector::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Release focusVodget when focus is not grabbed.
	// When focus is grabbed it is possible to re-enter our current focusVodget. If this occurs 
	// we keep track of the re-entry to prevent focus from being lost when focus grab is released.

}

void UDirectSelector::GrabFocus(bool val)
{
	focus_grabbed = val;

	// If focus grab is being released and we exited the focusVodget while grabbed
	// release the current focusVodget, otherwise our cursor is still overlapping focusVodget
	// and nothing needs to be changed.
	
}
