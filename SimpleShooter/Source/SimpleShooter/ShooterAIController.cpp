// Copyright Daniel Newsom 2021


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

AShooterAIController::AShooterAIController()
{
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(LineOfSightTo(PlayerPawn))
	{
		MoveToActor(PlayerPawn,AcceptanceRadius);
		SetFocus(PlayerPawn);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
