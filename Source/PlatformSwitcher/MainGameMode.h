// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMSWITCHER_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	const float FAR_LOCATION_X = 800.0f;
	const float NEAR_LOCATION_X = 1600.0f;

	APawn* player;
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void OnSwitch();
	void OnGameOver(bool win);

	bool Switched;
};
