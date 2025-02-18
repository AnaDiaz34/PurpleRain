// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Selector.h"
#include "EyeHandRaySelector.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAR_2025_API_API UEyeHandRaySelector : public USelector
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEyeHandRaySelector();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
	USceneComponent* dominantEye = nullptr;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void SetCursor() override;

	virtual void GrabFocus(bool val) override;

private:
	UVodget* DoRaycast();

	float ratioHitEyeOverHandEye = 0.0;

	// The hit result gets populated by the line trace
	FHitResult Hit;
};
