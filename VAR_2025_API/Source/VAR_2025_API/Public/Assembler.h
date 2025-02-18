// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grabber.h"
#include "Assembler.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAR_2025_API_API UAssembler : public UGrabber
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	/** called when something enters the sphere component */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Focus(USelector* cursor, bool state) override;
	virtual void ForePinch(USelector* selector, bool state) override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector grabvec;
	FVector grabvecAfterSnap;
	class USphereComponent* pinDock = nullptr;
	float unsnapDistSq = 15625.0; // Pin colliders are 50cm diameter, therefore no collision at 100cm, add 25cm for clean exit.
	bool grabvecAfterSnapSet = false;
	bool isDocked = false;
};
