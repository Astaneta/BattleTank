// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank controlled"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing: %s"), *(ControlledTank->GetName()))
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if(GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D((ViewportSizeX * CrossHairXLocation),(ViewportSizeY * CrossHairYLocation));
	FVector LookDirection;

	// if we look at some direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along that look direction, and see what we hit (at max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	
	return true;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector endVector, FVector &OutHitLocation) const
{
	// Create a bool var for return the LineTraceSingleByChannel method
	bool bIsHitted;
	// Calculate the Start of the vector
	FVector StartVector = PlayerCameraManager->GetCameraLocation();
	// Calculate the End of the Vector
	FVector EndVector = StartVector + (endVector * LineTraceRange);
	// Create an HitResult
	FHitResult HitResult;
		// Use the LineTraceSingleByChannel method passing the OutHitLocation paramether
	bIsHitted = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartVector,
		EndVector,
		ECollisionChannel::ECC_Visibility
	);
	if(bIsHitted)
	{
		OutHitLocation = HitResult.Location;
	}
	else { OutHitLocation = FVector(0.0f); }

	return bIsHitted;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}