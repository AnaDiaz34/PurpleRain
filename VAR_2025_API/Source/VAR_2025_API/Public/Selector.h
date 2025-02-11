#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Selector.generated.h"

class UVodget;
class UMotionControllerComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAR_2025_API_API USelector : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USelector();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
	USceneComponent* hand = nullptr;

	// When a selectors focus is grabbed(true) by a Vodget client (focusVodget), the Selector cannot focus
	// on another vodget client until GrabFocus(false) is called by focusVodget releasing the grab.
	virtual void GrabFocus(bool val)
	{
		focus_grabbed = val;
	}

	// Inheriting selectors must all maintain a model of a 3D cursor in world coordinates. 
	const FTransform& Cursor();

	UFUNCTION(BlueprintCallable, Category = "VAR")
	void ForePinch(const bool Value);

	UFUNCTION(BlueprintCallable, Category = "VAR")
	void MiddlePinch(const bool Value);

	UFUNCTION(BlueprintCallable, Category = "VAR")
	void Grip(const bool Value);

protected:

	// Inheriting selectors must all override SetCursor() to set FTransform cursor based on the selection method. 
	virtual void SetCursor();
	FTransform cursor;

	// The focusVodget is the current selected vodget maintained by each inheriting selector.
	UVodget* focusVodget = nullptr;

	// Set when client vodgets call GrabFocus() above.
	bool focus_grabbed = false;
};
