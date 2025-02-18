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
	UVodget* retval = nullptr;

	// Search for vodgets starting at your dominant eye in the direction passing through the controllers marker.

	return retval;
}

void UEyeHandRaySelector::GrabFocus(bool val)
{
	Super::GrabFocus(val);

	if (focus_grabbed) {
		// Calculate the hit-eye / hand-eye ratio the moment focus is grabbed.

	}
}

void UEyeHandRaySelector::SetCursor()
{

	// Set cursor to the scaled world grab location when focusVodget exists and focus is grabbed.
	//FVector EyePos = head->GetComponentTransform().TransformPosition(dominantEyeOffset);

	// When not grabbed, set cursor to the hit point when focusVodget exists otherwise set to the controller location.

}

// Called every frame
void UEyeHandRaySelector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}