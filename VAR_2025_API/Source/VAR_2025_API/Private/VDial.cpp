#include "VDial.h"

void UVDial::Focus(USelector* cursor, bool state)
{
	// Optional: Change some property of the clients material to highlight when focused. 
}

void UVDial::ForePinch(USelector* selector, bool state)
{
	// ToDo: On Trigger button true, convert the world cursors position into local client space and
	// Don't forget to grab and release selector focus appropriately.
	selector->GrabFocus(state);
	PrimaryComponentTick.SetTickFunctionEnable(state);
	grabbingSelector = selector;
	if (state)
	{
		FVector worldPosition = grabbingSelector->Cursor().GetLocation();
		FVector localPosition = clientComponent->GetComponentTransform().InverseTransformPosition(worldPosition);
		//DegreesToRadians()
		// save the grabvec in the plane along which the dial spins.
		grabvec = FVector(0.0f, localPosition.Y, localPosition.Z);
	}
}

void UVDial::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ToDo: While grabbing operation is active, calculate the current value of the world cursor in the 
	// dials local plane and calculate quaternion that would rotate the initial grabvec into the current.
	// Use this quaternion to spin the dial to follow the grabbing world cursor.
	if (grabbingSelector)
	{
		FVector worldPosition = grabbingSelector->Cursor().GetLocation();
		FVector localPosition = clientComponent->GetComponentTransform().InverseTransformPosition(worldPosition);

		FVector currentVect = FVector(0.0f, localPosition.Y, localPosition.Z);

		FQuat deltaQ = FQuat::FindBetweenVectors(grabvec, currentVect);
		//FVector testvec = dq * grabvec; This is what the previous line does

		clientComponent->AddRelativeRotation(deltaQ);

	// Once the dial is spinning freely we need to calculate the angle of the dials notch with its parent notch.
	// Determine the unit "notch" vector that points toward the dials notch in the dials local space.
		FVector notchVector = FVector::UpVector;
	// Rotate the notch vector by the dials local quaternion and use the dot product with the unrotated notch vector 
	// to calculate the radians between these vectors and convert the radians to degrees.

	//Step 1. Rotate the notch vector by the dials local quaternion
		FQuat dialsLocal = clientComponent->GetRelativeRotation().Quaternion();

		FVector roatedVector = dialsLocal.RotateVector(notchVector);
	//Step 2. In order to calculate the radians between these vectors, use dot product with the notchVector and the now rotated notch vector
		float radiansBetweenVectors = FMath::Acos(FVector::DotProduct(roatedVector, notchVector));
	//Step 3. Now, convert the radians to degrees
		//float convertedValue = radiansBetweenVectors.RadiansToDegrees();
		float convertedValue = FMath::RadiansToDegrees(radiansBetweenVectors);

		//FQuat dialsLocalQuaternion = clientComponent->GetRelativeRotation().Quaternion();
		//FVector rotatedNotchVector = FVector::DotProduct(, notchVector);
		//UE_LOG(LogTemp, Warning, TEXT("Rotate:%f"), roatedVector.Y);

	// As you now spin the dial the degrees will go from 0..180 and back to 0.
	// Look at the XYZ components of the rotated vector and determine which value is positive/negative when degrees
	// should be 0..180 or 180..360. Use this to broadcast a value from 0..360 to a DialDelegate.
		//if (convertedValue < 0)
		//{
		//	convertedValue += 360;
		//}

		/*if (convertedValue > 180)
		{
			convertedValue -= 360;
		}*/

		if (roatedVector.Y > 0)
		{
			convertedValue = 360 - convertedValue;
		}

		DialDelegate.Broadcast(convertedValue);

	}

}
