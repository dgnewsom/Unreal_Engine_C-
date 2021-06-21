// Copyright Daniel Newsom 2021


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"
#include "GameFramework/Controller.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp,Warning,TEXT("%s was killed!"),*PawnKilled->GetName());
	
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if(PlayerController != nullptr)
	{
		EndGame(false);
	}

	for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if(!AIController->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for(AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
	}
}
