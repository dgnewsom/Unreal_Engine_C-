// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	//Get references and game win/lose conditions
	//Call handleGameStart to initialize start countdown, turret activation, pawn check etc
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	//what actor died if turret add to score, if player lose -> condition
}

void ATankGameModeBase::HandleGameStart()
{
	//Initialize start countdown, turret activation, pawn check etc
	//Call blueprint version GameStart
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	//See if player killed all turrets, show win.
	//if player died lose result
	//Call blueprint version GameOver(bool).
}


