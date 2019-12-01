// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class S01_PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, Category = "Speed")
	float PlatformSpeed = 50; // cm/s

public:

	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;
	
};
