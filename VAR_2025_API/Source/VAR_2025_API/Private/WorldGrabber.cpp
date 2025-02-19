// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldGrabber.h"
#include "Components/SceneComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UWorldGrabber::UWorldGrabber()
{
	// Set this component to be ticked every frame.  
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

//New actualy method name should be SetCursor() but can't change the name due to errors that would arrise
void UWorldGrabber::SetLocalCursor()
{
	if (leftGrabbing && rightGrabbing)
	{
		// Set the cursor position to the average world location of both hands
		FVector left = leftHand->GetComponentLocation();
		FVector right = rightHand->GetComponentLocation();

		cursorsrt.SetLocation((left + right) * 0.5f);
		// Set the cursor rotation to the FRotationMatrix::MakeFromXZ where X is the vector between the hands and Z is up.
		// If dollyMode constrain rotation to rotate about Z up only.

		FVector xAxis = left - right;
		FVector zAxis = FVector::UpVector;
		FMatrix rotation = FRotationMatrix::MakeFromXZ(xAxis, zAxis);
		cursorsrt.SetRotation(rotation.ToQuat());

		if (dollyMode)
		{
			FVector wonkyUP = cursorsrt.GetRotation() * FVector::UpVector;
			//want the quat that rotates wonky up to up vector and if
			FQuat correctQuat = FQuat::FindBetweenVectors(wonkyUP, FVector::UpVector);
			FQuat correctRotation = correctQuat * cursorsrt.GetRotation();

			cursorsrt.SetRotation(correctRotation);
			
		}

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
		cursorsrt = leftHand->GetComponentTransform();
		cursorsrt.SetRotation(FQuat::Identity);
	}
	else if (rightGrabbing)
	{
		cursorsrt = rightHand->GetComponentTransform();
		cursorsrt.SetRotation(FQuat::Identity);
	}
}

void UWorldGrabber::LWorldGrab(const bool Value)
{
	leftGrabbing = Value;
	UE_LOG(LogTemp, Warning, TEXT("WorldGrabber LEFT:%s"), *FString((Value) ? "GRAB" : "RELEASE"));
	GrabChanged();
}

void UWorldGrabber::RWorldGrab(const bool Value)
{
	rightGrabbing = Value;
	UE_LOG(LogTemp, Warning, TEXT("WorldGrabber RIGHT:%s"), *FString((Value) ? "GRAB" : "RELEASE"));
	GrabChanged();
}

void UWorldGrabber::GrabChanged()
{
	PrimaryComponentTick.SetTickFunctionEnable(leftGrabbing || rightGrabbing);
	// Reset worldsrt whenever the grab cursor configuration changes.
	worldsrt = FTransform::Identity;

	// Save the distance between hands when bimanual scaling is enabled. 
	initialBimanualHandDist = rightHand - leftHand;

	// Save the worldsrt as a child of the updated cursor(cursor is our hand in this case, or the cursorsrt).
	SetLocalCursor();
	//rightHand->GetOwner()->AddComponent(worldsrt);
	//Note: childsrt = cursorsrt.Invsere() * worldsrt; would work as the lower code, but only if we havne't set worldsrt to Identity like we did
	//before
	childsrt = cursorsrt.Inverse();

}

void UWorldGrabber::DollyToggle(const bool Value) { dollyMode = !dollyMode; }
void UWorldGrabber::ScaleToggle(const bool Value) { scaleMode = !scaleMode; }

// Called every frame
void UWorldGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate where the worldsrt would be IF we could actually move the world.

	//Dont forget to change the cursor
	SetLocalCursor();

	//Where would the world be now
	worldsrt = childsrt * cursorsrt;

	// Then calculate where the current pawn would be as a child of that changed world.
	FTransform meAsAChildOfTheWorld = GetOwner()->GetRootComponent()->GetComponentTransform() * worldsrt.Inverse();
	// Set the pawn to your result.
	GetOwner()->SetActorTransform(meAsAChildOfTheWorld);
}
