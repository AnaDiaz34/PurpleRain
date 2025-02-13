#pragma once

#include "CoreMinimal.h"
#include "Vodget.h"
#include "VSlider.generated.h"

// Define a float variable delegate that multiple blueprint clients can register callbacks for when the value changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSliderDelegate, float, SliderPct);

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAR_2025_API_API UVSlider : public UVodget
{
	GENERATED_BODY()

public:
	virtual void Focus(USelector* cursor, bool state) override;
	virtual void ForePinch(USelector* cursor, bool state) override;

	UPROPERTY(BlueprintAssignable, Category = "VAR")
	FSliderDelegate SliderDelegate;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	USelector* grabbingSelector = nullptr;
	float initialgrabval;
	float minval = -73.0;
	float maxval = 73.0;
};