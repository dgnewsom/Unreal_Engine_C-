// Copyright Daniel Newsom 2021


#include "ShooterAIController.h"

#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AShooterAIController::AShooterAIController()
{
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*if(LineOfSightTo(PlayerPawn))
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),PlayerPawn->GetActorLocation());
	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}*/
	
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if(ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	
	return true;
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
	}
	//PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
