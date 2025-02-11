#pragma once

#include "CoreMinimal.h"
#include "Selector.h"
#include "RaySelector.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VAR_2025_API_API URaySelector : public USelector
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URaySelector();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VAR")
	USceneComponent* marker = nullptr;

protected:
	virtual void SetCursor() override;

private:
	UVodget* DoRaycast();

};
