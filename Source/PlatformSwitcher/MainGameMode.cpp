// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"
#include "GameWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	//player = GetWorld()->GetFirstPlayerController()->GetPawn();

	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("Switch", IE_Pressed, this, &AMainGameMode::OnSwitch);
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("Restart", IE_Pressed, this, &AMainGameMode::OnRestart).bExecuteWhenPaused = true;

	ChangeMenuWidget(StartingWidgetClass);
	((UGameWidget*)CurrentWidget)->Load();

	FText startingMessage = FText::FromString(FString(TEXT("Race to the orb!")));
	((UGameWidget*)CurrentWidget)->SetMessageText(startingMessage);
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
	FVector newLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// Adjust the X location
	newLocation.X = newX;

	// Set new location
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(newLocation);
}

void AMainGameMode::OnGameOver(bool win)
{
	((UGameWidget*)CurrentWidget)->OnGameOver(win);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMainGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AMainGameMode::OnRestart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}