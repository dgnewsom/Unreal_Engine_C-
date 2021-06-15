// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> AllTurrets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), AllTurrets);
	return AllTurrets.Num();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if(DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		GameOver(false);
	}
	else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if(--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	//Initialize start countdown, turret activation, pawn check etc
	//Call blueprint version GameStart
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
	GameStart();
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	//See if player killed all turrets, show win.
	//if player died lose result
	//Call blueprint version GameOver(bool).
	GameOver(PlayerWon);
}


