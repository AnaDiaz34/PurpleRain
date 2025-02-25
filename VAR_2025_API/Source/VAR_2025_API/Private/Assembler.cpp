// Fill out your copyright notice in the Description page of Project Settings.

//notes!
//when you are in grabber mode DONT COPY THE GRABBER CODE youre a grabber silly!!!

//without letting go want 


#include "Assembler.h"

#include "Assembler.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshSocket.h"

// Called when the game starts
void UAssembler::BeginPlay()
{
	Super::BeginPlay();

	// Setup overlap callbacks. 
	pinDock = clientComponent->GetOwner()->FindComponentByClass<USphereComponent>();
	clientComponent = Cast<UStaticMeshComponent>(GetOwner()->FindComponentByClass<UStaticMeshComponent>());
	if (pinDock)
	{
		pinDock->OnComponentBeginOverlap.AddDynamic(this, &UAssembler::OnOverlapBegin);
	}
}

void UAssembler::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ToDo: When the pinDock mesh on the wheel overlaps the pinDock mesh on the rotor, reparent "dock" the wheel
	// to the rotor.
	FString resultString;
	OtherComp->GetName(resultString);
	UE_LOG(LogTemp, Warning, TEXT("OnOverLapBegin:%s"), *resultString);
	USphereComponent* wheelPin = clientComponent->GetOwner()->FindComponentByClass<USphereComponent>();
	USphereComponent* rotorPin = OtherActor->FindComponentByClass<USphereComponent>();

	if (OverlappedComp == wheelPin && OtherComp == rotorPin)
	{
		isDocked = true;
		if (rotorPin->DoesSocketExist(FName("PinSocket")))
		{
			FTransform transform = rotorPin->GetSocketTransform(FName("PinSocket"), RTS_World);
			clientComponent->AttachToComponent(rotorPin, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			clientComponent->SetWorldTransform(transform);
		}
		else
		{
			clientComponent->AttachToComponent(rotorPin, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			clientComponent->SetWorldTransform(rotorPin->GetComponentTransform());
		}

		grabvecAfterSnap = clientComponent->GetComponentLocation();
		grabvecAfterSnapSet = true;

		UE_LOG(LogTemp, Warning, TEXT("wheel docked to rotor"));
	}

}

void UAssembler::Focus(USelector* cursor, bool state)
{
	// Optional: Change some property of the clients material to highlight when focused. 
}

void UAssembler::ForePinch(USelector* selector, bool state)
{
	//UGrabber::ForePinch(selector, state);
	// ToDo: Use inherited Grabber functionality when in normal grabbing mode.
	// Add snap and rotation functionailty when snapped.
	if (!isDocked)//if wheel isnt docked its just a regualr grabber
	{
		UGrabber::ForePinch(selector, state);
		UE_LOG(LogTemp, Warning, TEXT("Turning the wheel to a regular grabber in forepinch"));
		return;	
	}

	selector->GrabFocus(state);
	if (state)
	{
		FVector handPosition = selector->Cursor().GetLocation();
		float grabDistanceSq = FVector::DistSquared(handPosition, grabvecAfterSnap);

		if (grabDistanceSq < unsnapDistSq)
		{
			grabbingSelector = selector;
			FVector worldPosition = grabbingSelector->Cursor().GetLocation();
			FVector localPosition = clientComponent->GetComponentTransform().InverseTransformPosition(worldPosition);
			grabvec = FVector(localPosition.X, localPosition.Y, 0.0f);
		}
	}
	else 
	{
		if (grabbingSelector == selector)
		{
			grabbingSelector = nullptr;
			selector->GrabFocus(false);
		}
	}

}

void UAssembler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//UGrabber::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ToDo: Move the wheel as a UGrabber when undocked.
	// Rotate the wheel on the rotor when docked.
	// Undock the wheel when significant stress is placed on the rotor-wheel joint.
	if (!isDocked)//if wheel isnt docked its just a regualr grabber
	{
		UGrabber::TickComponent(DeltaTime, TickType, ThisTickFunction);
		UE_LOG(LogTemp, Warning, TEXT("Turning the wheel to a regular grabber in tickcomponent"));
		return;

	}

	if (grabbingSelector)
	{
		FVector handPosition = grabbingSelector->Cursor().GetLocation();
		float grabDistanceSq = FVector::DistSquared(handPosition, grabvecAfterSnap);

		if (grabDistanceSq > unsnapDistSq)
		{
			UE_LOG(LogTemp, Warning, TEXT("wheel unsapped"));
			isDocked = false;
			grabvecAfterSnapSet = false;
			clientComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

			if (grabbingSelector)
			{
				FVector controllerPosition = grabbingSelector->Cursor().GetLocation();

				clientComponent->SetWorldLocation(controllerPosition);
			}
			return;
		}
		//rotation Logic
		FVector worldPosition = grabbingSelector->Cursor().GetLocation();
		FVector localPosition = clientComponent->GetComponentTransform().InverseTransformPosition(worldPosition);
		FVector currentVect = FVector(localPosition.X, localPosition.Y, 0.0f);

		FQuat deltaQ = FQuat::FindBetweenVectors(grabvec, currentVect);

		FQuat slerpQ = FQuat::Slerp(FQuat::Identity, deltaQ, 0.8f);
		clientComponent->AddRelativeRotation(slerpQ);

		//clientComponent->AddRelativeRotation(deltaQ);

		grabvec = currentVect;
	}
}
