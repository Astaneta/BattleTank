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
		UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString())
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	/*UWorld* World = GetWorld();
	FHitResult HitResult;
	FVector Location;
	FRotator Rotation;
	GetPlayerViewPoint(Location, Rotation);
	FVector RayCastEnd = Location + (Rotation.Vector() * 100000);
	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *Location.ToString(), *Rotation.Vector().ToString())
	bool HitTarget = GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			Location,
			RayCastEnd,
			ECollisionChannel::ECC_WorldStatic
		);
	OutHitLocation = HitResult.Location;
	if (HitTarget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit something"), *OutHitLocation.ToString())
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit nothing"), *OutHitLocation.ToString())
		return false;
	}*/

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D((ViewportSizeX * CrossHairXLocation),(ViewportSizeY * CrossHairYLocation));
	// De-project the screen position of the crosshair to a world direction
	// Line trace along that look direction, and see what we hit (at max range)
	return true;
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}