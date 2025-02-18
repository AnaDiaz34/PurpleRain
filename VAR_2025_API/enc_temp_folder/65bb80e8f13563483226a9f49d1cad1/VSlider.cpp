#include "VSlider.h"

void UVSlider::Focus(USelector* cursor, bool state)
{
	// Optional: Change some property of the clients material to highlight when focused. 
}

void UVSlider::ForePinch(USelector* selector, bool state)
{
	// ToDo: On Grab true, convert the world cursors position into local client space and
	//turn on tick when true turn off when false
	selector->GrabFocus(state);
	PrimaryComponentTick.SetTickFunctionEnable(state);
	grabbingSelector = selector;

	if (state)
	{
		//FVector worldvec = transform->TransformPosition(localvec);
		//FVector localvec = transform->InverseTransformPosition(worldvec);
		//USceneComponent cursor = Cast<USceneComponent>(selector->Cursor());
		//FTransform cursor = selector->Cursor();
		FVector worldPosition = grabbingSelector->Cursor().GetLocation();
		FVector localPosition = clientComponent->GetComponentTransform().InverseTransformPosition(worldPosition);
		// save the initialgrabval of the axis along which the slider knob moves.
		initialgrabval = localPosition.Z;

		//UE_LOG(LogTemp, Warning, TEXT("Initial:%f"), initialgrabval );
	} else {
	//FTransform cursor = selector->Cursor().GetLocation().Z;
	//FTransform worldPosition = cur
	//FTransform worldPosition = Get
	//FTransform localPosition = InverseTransformPosition(worldLocation);
	//initialgrabval = localLocation.Z?;
	
	// Don't forget to grab and release selector focus appropriately.

		Focus(grabbingSelector, false);
		//turn off tick
		PrimaryComponentTick.SetTickFunctionEnable(state);
	}
}

void UVSlider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ToDo: While grabbing operation is active, calculate the current value of the world cursor along the 
	// local movement axis. Move the client along this local axis so that the current value matches 
	// the initial value again. 
	if (grabbingSelector)
	{
		FVector worldPosition = grabbingSelector->Cursor().GetLocation();
		FVector localPosition = clientComponent->GetComponentTransform().InverseTransformPosition(worldPosition);
		//UE_LOG(LogTemp, Warning, TEXT("LocalPos:%f %f %f"), localPosition.X, localPosition.Y, localPosition.Z);

		float currentVal = localPosition.Z;

		//UE_LOG(LogTemp, Warning, TEXT("Current:%f"), currentVal);

	// Once the knob is following the cursor correctly along the movement axis, clamp the motion to keep
	// the knob inside its slot.
		float deltaZ = currentVal - initialgrabval;
		FVector currentPos = clientComponent->GetRelativeLocation();

		//currentPos.Set(currentPos.X, currentPos.Y, currentPos.Z + deltaZ);
		currentPos.Z = FMath::Clamp(currentPos.Z + deltaZ, minval, maxval);
		//currentPos.Z += deltaZ;

		clientComponent->SetRelativeLocation(currentPos);
		// Once the knob is moving correctly within its slot calculate the percentage that the knob is between
		// its minimum and maximum value and broadcast the percentage to all callbacks registered to SliderDelegate.
		// e.g.: SliderDelegate.Broadcast(pct);
		float pct = (currentPos.Z - minval) / (maxval - minval);
		SliderDelegate.Broadcast(pct);
	}
}
