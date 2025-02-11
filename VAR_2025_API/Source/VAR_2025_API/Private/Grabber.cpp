#include "Grabber.h"

void UGrabber::Focus(USelector* selector, bool state)
{
	// Optional: Change some property of the clients material to highlight when focused. 
	UVodget::Focus(selector, state);
}

void UGrabber::ForePinch(USelector* selector, bool state)
{
	// ToDo: On Grab button true, set childsrt to the clients transform as a child of the selectors cursor.
	// You must also grab the selectors focus during the grab and release it when finished.

	// We grab the selectors focus when grabbing is true to ensure recieving focusUpdate until grabbing is released.
	selector->GrabFocus(state);
	if (state) {
		// Save the grabbing selector.

		// Set childsrt to the clients transform as a child of the selectors cursor.
	}
	else {
		// Clear the grabbing selector.
	}
	
	// Use PrimaryComponentTick.SetTickFunctionEnable to turn tick on when grabbing and off when not grabbing.
	
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ToDo: While grabbing operation is active convert the childsrt that was set when grabbing began back
	// to world space and set the clients world transform to the result.

}