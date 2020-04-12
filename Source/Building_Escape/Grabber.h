// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 150.f;
	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *InputComponent = nullptr;

	void CheckForPhysicsHandle();
	void SetupInput();
	void Grab();
	void StopGrabbing();

	// Returning First Actor Within Reach
	// Const Cause We Dont Want It Changing What Its Been Hit By
	FHitResult GetFirstPhysicsBodyInReach() const;

	// Get The Players Position In The World
	FVector GetPlayersWorldLocation() const;

	// Return LineTraceEnd
	FVector GetPlayersReach() const;
};
