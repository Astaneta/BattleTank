// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, +1.0);
	auto Rotation = RelativeSpeed * MaxRotationSpeed * GetWorld()->GetDeltaSeconds();
	auto NewRotation = RelativeRotation.Yaw + Rotation;

	SetRelativeRotation(FRotator(0, NewRotation, 0));

}


