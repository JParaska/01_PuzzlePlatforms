// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);

		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	}
}

void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (HasAuthority() && ActiveTriggers > 0) {
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		SetActorLocation(GetActorLocation() + (PlatformSpeed * DeltaTime * Direction));
		if (GlobalStartLocation.Equals(GetActorLocation(), 5)) {
			SwaptStartAndTarget();
		}
		if (GlobalTargetLocation.Equals(GetActorLocation(), 5)) {
			SwaptStartAndTarget();
		}
	}
}

void AMovingPlatform::SwaptStartAndTarget() {
	FVector Temp = GlobalStartLocation;
	GlobalStartLocation = GlobalTargetLocation;
	GlobalTargetLocation = Temp;
}

void AMovingPlatform::AddActiveTrigger() {
	ActiveTriggers += 1;
}

void AMovingPlatform::RemoveActiveTrigger() {
	ActiveTriggers = FMath::Max(0, ActiveTriggers - 1);
}
