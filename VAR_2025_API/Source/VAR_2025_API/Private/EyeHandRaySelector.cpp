// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeHandRaySelector.h"
#include "MotionControllerComponent.h"
#include "Vodget.h"


// Sets default values for this component's properties
UEyeHandRaySelector::UEyeHandRaySelector()
{
}

UVodget* UEyeHandRaySelector::DoRaycast()
{
	// Search for vodgets starting at your dominant eye in the direction passing through the controllers marker.
	UVodget* retval = nullptr;

	// Set FCollisionQueryParams to customize various properties about the trace

	FCollisionQueryParams Params;
	//note this pretty much ignores us(our controller/hand)
	Params.AddIgnoredActor(GetOwner());

	// Use LineTraceSingleByChannel to find Vodgets
	// Move the marker to the controller world location when no vodget is found otherwise move to the hit point.

	FVector Start(dominantEye->GetComponentLocation());
	FVector End(Start + ((hand->GetComponentLocation() - Start) * 1000.0));
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_PhysicsBody, Params, FCollisionResponseParams());

	// Move the marker to the controller world location when no vodget is found otherwise move to the hit point.
	//if something is hit check if its a vodget
	//UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(scenecomponent);
	FVector selectedPosition;
	if (bHit)
	{
		selectedPosition = Hit.Location;

		USceneComponent* foundComponent = Cast<USceneComponent>(Hit.Component);
		if (foundComponent != nullptr)
		{
			for (size_t i = 0; i < foundComponent->GetNumChildrenComponents(); i++)
			{
				retval = Cast<UVodget>(foundComponent->GetChildComponent(i));
				if (retval != nullptr)
				{
					break;
				}
			}
		}
	}
	else
	{
		selectedPosition = Start;
	}

	return retval;
}

void UEyeHandRaySelector::GrabFocus(bool val)
{
	Super::GrabFocus(val);

	if (focus_grabbed) {
		FVector Start(dominantEye->GetComponentLocation());
		//FVector End(Start + ((hand->GetComponentLocation() - Start) * 1000.0));
		float eyeToHit = (Hit.Location - Start).Size();
		float eyeToHand = (hand->GetComponentLocation() - Start).Size();
		// Calculate the hit-eye / hand-eye ratio the moment focus is grabbed.
		ratioHitEyeOverHandEye = eyeToHit / eyeToHand;
	}
	//grab focus derive where the 3d cursor is 
	//save the last hitpoint and save the distance between the eye and last hitpoint(one float)
	//wheres the distance 
	//
}

void UEyeHandRaySelector::SetCursor()
{

	// Set cursor to the scaled world grab location when focusVodget exists and focus is grabbed.
	//FVector EyePos = head->GetComponentTransform().TransformPosition(dominantEyeOffset);
	if (focusVodget != nullptr && focus_grabbed)
	{
		FVector handLocation = hand->GetComponentLocation();
		FVector eyeLocation = dominantEye->GetComponentLocation();
		FVector newLocation = (eyeLocation + (handLocation - eyeLocation) * ratioHitEyeOverHandEye);
		FQuat handRotation = hand->GetComponentRotation().Quaternion();

		cursor.SetLocation(newLocation);
		cursor.SetRotation(handRotation);

	}
	else if(focusVodget)
	{
		// When not grabbed, set cursor to the hit point when focusVodget exists otherwise set to the controller location.
		cursor.SetLocation(Hit.Location);
	}
	else if (hand)
	{
		cursor.SetLocation(hand->GetComponentLocation());
	}

}

// Called every frame
void UEyeHandRaySelector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!focus_grabbed)
	{
		UVodget* hitVodget = DoRaycast();

		if (hitVodget != focusVodget)
		{
			if (focusVodget)
			{
				focusVodget->Focus(this, false);
			}
			focusVodget = hitVodget;
			if (focusVodget)
			{
				focusVodget->Focus(this, true);
			}
		}
	}
}