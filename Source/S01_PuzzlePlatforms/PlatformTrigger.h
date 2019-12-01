// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformTrigger.generated.h"

UCLASS()
class S01_PUZZLEPLATFORMS_API APlatformTrigger : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	class UBoxComponent* TriggerVolume;
	
public:	
	// Sets default values for this actor's properties
	APlatformTrigger();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
