// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle %f"), *Name, Throttle)

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

	auto ForceLocation = GetComponentLocation();

	// GetOwner punta al blueprint tank, root component al root che è il tank inteso come static mesh
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	/*
	Il Cast viene fatto perché la GetRootComponent ritorna una UScene, la quale non può ricevere una forza applicata. Quindi viene fatto il cast alla UPrimitive,
	che in teoria dovrebbe non dare problemi perché già di base il root è una StaticMesh
	*/

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


