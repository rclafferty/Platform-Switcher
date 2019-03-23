// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"
#include "Engine/World.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	//player = GetWorld()->GetFirstPlayerController()->GetPawn();

	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("Switch", IE_Pressed, this, &AMainGameMode::OnSwitch);
}

void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainGameMode::OnSwitch()
{
	Switched = !Switched;

	float newX = 0;

	if (Switched)
	{
		newX = FAR_LOCATION_X;
	}
	else
	{
		newX = NEAR_LOCATION_X;
	}

	// Get current location
	FVector newLocation = player->GetActorLocation();

	// Adjust the X location
	newLocation.X = newX;

	// Set new location
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(newLocation);
}