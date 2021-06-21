// Copyright Daniel Newsom 2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
		
public:
	AShooterAIController();
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 300.f;
	APawn* PlayerPawn;
};
