// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//Set a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // Assuming 40 tonn tank and 1g acceleration
};
