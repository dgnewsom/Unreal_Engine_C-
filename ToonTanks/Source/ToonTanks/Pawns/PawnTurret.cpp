// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	if(ShowAttackRadius)
	{
		DrawDebugSphere(GetWorld(),GetOwner()->GetActorLocation(),AttackRadius,24,FColor(255,0,0),true,1,0,1);
	}
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
}


// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerPawn || ReturnDistanceToPlayer() > AttackRadius){return;}
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	// If Player == null || is dead then return.
	if(!PlayerPawn)	{return;}

	if(ReturnDistanceToPlayer() <= AttackRadius)
	{
		// Player is in range then fire.
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if(!PlayerPawn)	{return 0.0f;}
	return FVector::Dist(PlayerPawn->GetActorLocation(),GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}