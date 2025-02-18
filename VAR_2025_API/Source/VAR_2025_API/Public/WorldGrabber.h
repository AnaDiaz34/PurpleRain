// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldGrabber.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAR_2025_API_API UWorldGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWorldGrabber();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
	USceneComponent* leftHand;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
	USceneComponent* rightHand;

	// Bluprint mappable world grabber input functions
	UFUNCTION(BlueprintCallable, Category = "VAR")
	void LWorldGrab(const bool Value);

	UFUNCTION(BlueprintCallable, Category = "VAR")
	void RWorldGrab(const bool Value);

	UFUNCTION(BlueprintCallable, Category = "VAR")
	void DollyToggle(const bool Value);

	UFUNCTION(BlueprintCallable, Category = "VAR")
	void ScaleToggle(const bool Value);

private:

	void SetLocalCursor();

	bool leftGrabbing = false;
	bool rightGrabbing = false;

	FTransform childsrt;
	FTransform worldsrt;
	FTransform cursorsrt;
	float initialBimanualHandDist;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GrabChanged();

	bool dollyMode = true;
	bool scaleMode = false;
	float initialWorldToMeters = 100.0;
	float currWorldToMeters = 100.0;
};
