// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerFinding = GetPlayerTank();
	if (!PlayerFinding)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player tank found"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController has found: %s"), *(PlayerFinding->GetName()))
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	APawn* PlayerTank = PlayerController->GetPawn();
	if (!PlayerTank)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerTank);
	}
}

