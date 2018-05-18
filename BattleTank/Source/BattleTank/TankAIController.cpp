// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		//Cast for tank class
		auto* ControlledTank = Cast<ATank>(GetPawn());

		//TODO move torward player

		//Aim toward the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire towars the player
		ControlledTank->Fire(); //TODO don't fire every frame
	}


}
