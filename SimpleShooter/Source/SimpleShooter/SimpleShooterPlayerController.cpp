// Copyright Daniel Newsom 2021


#include "SimpleShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ASimpleShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	HUDScreen->RemoveFromViewport();
	if(bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this,WinScreenClass);
		if(WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this,LoseScreenClass);
		if(LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer,this, &APlayerController::RestartLevel,RestartDelay);
}

void ASimpleShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	HUDScreen = CreateWidget(this,HUDClass);
		if(HUDScreen != nullptr)
		{
			HUDScreen->AddToViewport();
		}
}
