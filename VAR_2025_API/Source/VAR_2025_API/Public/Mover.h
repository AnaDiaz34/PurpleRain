// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAR_2025_API_API UMover : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

	UFUNCTION(BlueprintCallable, Category = "VAR")
	void MoveUpDown(const float value);

	UFUNCTION(BlueprintCallable, Category = "VAR")
	void Rotate(const float value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
