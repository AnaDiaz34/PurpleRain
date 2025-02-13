#include "VSlider.h"

void UVSlider::Focus(USelector* cursor, bool state)
{
	// Optional: Change some property of the clients material to highlight when focused. 
}

void UVSlider::ForePinch(USelector* selector, bool state)
{
	// ToDo: On Grab true, convert the world cursors position into local client space and
	selector->GrabFocus(true);
	FTransform worldPosition = 
	// save the initialgrabval of the axis along which the slider knob moves.
	// Don't forget to grab and release selector focus appropriately.
	selector->GrabFocus(false);
}

void UVSlider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ToDo: While grabbing operation is active, calculate the current value of the world cursor along the 
	// local movement axis. Move the client along this local axis so that the current value matches 
	// the initial value again. 

	// Once the knob is following the cursor correctly along the movement axis, clamp the motion to keep
	// the knob inside its slot.

	// Once the knob is moving correctly within its slot calculate the percentage that the knob is between
	// its minimum and maximum value and broadcast the percentage to all callbacks registered to SliderDelegate.
	// e.g.: SliderDelegate.Broadcast(pct);

}
