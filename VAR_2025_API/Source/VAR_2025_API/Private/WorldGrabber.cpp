// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldGrabber.h"
#include "Components/SceneComponent.h"
#include <Kismet/GameplayStatics.h>

//#include <VRPawn.h> giving me errors

// Sets default values for this component's properties
UWorldGrabber::UWorldGrabber()
{
	// Set this component to be ticked every frame.  

}

void UWorldGrabber::SetLocalCursor()
{
	if (leftGrabbing && rightGrabbing)
	{
		// Set the cursor position to the average world location of both hands
		FVector left = leftHand->GetComponentLocation();
		FVector right = rightHand->GetComponentLocation();

		// Set the cursor rotation to the FRotationMatrix::MakeFromXZ where X is the vector between the hands and Z is up.
		// If dollyMode constrain rotation to rotate about Z up only.

		if (scaleMode) {
#ifdef WORLDTOMETERS_SCALING
			// The VR Pawn is made larger/smaller in Unreal by changing the WorldToMeters setting.
			// Pawn geometry like the markers attached to controllers is the responsibility of the application.
			// https://forums.unrealengine.com/t/changing-the-player-pawn-camera-size/384747/3

			// As scale makes a VR pawn larger or smaller it changes the bimanual hand distance.
			float currBimanualHandDist = (left - right).Length();

			// The players bimanual hand distance needs to be adjusted to the initial scale.
			float ds = initialWorldToMeters / currWorldToMeters;
			currBimanualHandDist *= ds;

			// The direct world scaling ratio is opposite cursor scaling.
			ds = initialBimanualHandDist / currBimanualHandDist;
			currWorldToMeters = initialWorldToMeters * ds;
			GetWorld()->GetWorldSettings()->WorldToMeters = currWorldToMeters;

			// Scale the Pawns geometry, Note: WorldToMeters base is 100.
			float handScale = currWorldToMeters / 100.0;
			leftHand->SetWorldScale3D(FVector::OneVector * handScale);
			rightHand->SetWorldScale3D(FVector::OneVector * handScale);
#else
			// Scale the cursor by the ratio of current and initial distance between the hands.
			// Note: Scaling the Pawn in Unreal is best done by changing the WorldToMeters setting.
#endif
		}
		else
		{
			cursorsrt.SetScale3D(FVector::OneVector);
		}
	}
	else if (leftGrabbing)
	{
	}
	else if (rightGrabbing)
	{
	}
}

void UWorldGrabber::LWorldGrab(const bool Value)
{
	leftGrabbing = Value;
	//UE_LOG(LogTemp, Warning, TEXT("WorldGrabber LEFT:%s"), *FString((lController != nullptr) ? "GRAB" : "RELEASE"));
	GrabChanged();
}

void UWorldGrabber::RWorldGrab(const bool Value)
{
	rightGrabbing = Value;
	//UE_LOG(LogTemp, Warning, TEXT("WorldGrabber RIGHT:%s"), *FString((rController != nullptr) ? "GRAB" : "RELEASE"));
	GrabChanged();
}

void UWorldGrabber::GrabChanged()
{
	// Reset worldsrt whenever the grab cursor configuration changes.

	// Save the distance between hands when bimanual scaling is enabled. 
	
	// Save the worldsrt as a child of the updated cursor.
}

void UWorldGrabber::DollyToggle(const bool Value) { dollyMode = !dollyMode; }
void UWorldGrabber::ScaleToggle(const bool Value) { scaleMode = !scaleMode; }

// Called every frame
void UWorldGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate where the worldsrt would be IF we could actually move the world.

	// Then calculate where the current pawn would be as a child of that changed world.

	// Set the pawn to your result.

}
