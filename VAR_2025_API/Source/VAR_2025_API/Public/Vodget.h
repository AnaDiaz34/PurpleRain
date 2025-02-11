#pragma once

#include "Selector.h"

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Vodget.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAR_2025_API_API UVodget : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UVodget();

	virtual void Focus(USelector* cursor, bool state);
	virtual void ForePinch(USelector* cursor, bool state);
	virtual void MiddlePinch(USelector* cursor, bool state);
	virtual void Grip(USelector* cursor, bool state);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	USceneComponent* clientComponent = nullptr;
};

