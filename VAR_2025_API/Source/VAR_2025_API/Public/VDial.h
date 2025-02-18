#pragma once

#include "CoreMinimal.h"
#include "Vodget.h"
#include "VDial.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialDelegate, float, DialDegrees);

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAR_2025_API_API UVDial : public UVodget
{
	GENERATED_BODY()

public:
	virtual void Focus(USelector* cursor, bool state) override;
	virtual void ForePinch(USelector* cursor, bool state) override;

	UPROPERTY(BlueprintAssignable, Category = "VAR")
	FDialDelegate DialDelegate;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	USelector* grabbingSelector = nullptr;
	FVector grabvec;
};

