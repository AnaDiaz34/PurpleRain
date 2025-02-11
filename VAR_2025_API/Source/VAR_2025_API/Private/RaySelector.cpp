#include "RaySelector.h"
#include "Vodget.h"
#include "MotionControllerComponent.h"

// Sets default values for this component's properties
URaySelector::URaySelector()
{
}

UVodget* URaySelector::DoRaycast()
{
	UVodget* retval = nullptr;

	// Set FCollisionQueryParams to customize various properties about the trace


	// Use LineTraceSingleByChannel to find Vodgets.


	// Move the marker to the controller world location when no vodget is found otherwise move to the hit point.


	return retval;
}

void URaySelector::SetCursor()
{
	// Set the cursor to the marker world location.
	// Note: Marker is a child of the controller and will remain at the last known hit point in relative space.

}

// Called every frame
void URaySelector::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Search for Vodget components when focus is not grabbed.
	if (!focus_grabbed)
	{
		UVodget* hitVodget = DoRaycast();

		// If a vodgets is found, give it focus and begin forwarding any events while it still has focus.
		// Don't forget to notify any previous focusvodget that its lost focus and any new focusvodget that
		// it now has focus.
		if (hitVodget != focusVodget)
		{
			// If hitVodget exists, let any previous focusVodget know that it has lost focus here.

			// Set focusVodget to hitVodget (could be nullptr).
			focusVodget = hitVodget;

			// If focusVodget exists, let the newly found focusVodget know that it now has selector focus here.

		}

	}

}

