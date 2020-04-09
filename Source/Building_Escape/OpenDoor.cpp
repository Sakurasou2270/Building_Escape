// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	// += Compound Assignment Operator
	TargetYaw += InitialYaw;
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Has No Pressure Plate"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
	OpenDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float Seconds)
{
	// CurrentYaw = FMath::(CurrentYaw, TargetYaw, DeltaTime, 2);
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, Seconds * .75);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}
