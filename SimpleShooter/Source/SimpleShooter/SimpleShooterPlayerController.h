// Copyright Daniel Newsom 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SimpleShooterPlayerController.generated.h"


UCLASS()
class SIMPLESHOOTER_API ASimpleShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;
	
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;
	FTimerHandle RestartTimer;
	
};
