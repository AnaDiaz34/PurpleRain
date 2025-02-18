#include "VDial.h"

void UVDial::Focus(USelector* cursor, bool state)
{
	// Optional: Change some property of the clients material to highlight when focused. 
}

void UVDial::ForePinch(USelector* selector, bool state)
{
	// ToDo: On Trigger button true, convert the world cursors position into local client space and
	// save the grabvec in the plane along which the dial spins.
	// Don't forget to grab and release selector focus appropriately.

}

void UVDial::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ToDo: While grabbing operation is active, calculate the current value of the world cursor in the 
	// dials local plane and calculate quaternion that would rotate the initial grabvec into the current.
	// Use this quaternion to spin the dial to follow the grabbing world cursor.

	// Once the dial is spinning freely we need to calculate the angle of the dials notch with its parent notch.
	// Determine the unit "notch" vector that points toward the dials notch in the dials local space.
	// Rotate the notch vector by the dials local quaternion and use the dot product with the unrotated notch vector 
	// to calculate the radians between these vectors and convert the radians to degrees.

	// As you now spin the dial the degrees will go from 0..180 and back to 0.
	// Look at the XYZ components of the rotated vector and determine which value is positive/negative when degrees
	// should be 0..180 or 180..360. Use this to broadcast a value from 0..360 to a DialDelegate.

}
