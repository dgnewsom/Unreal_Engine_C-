// Copyright Daniel Newsom 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealthBarValue() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void Shoot();

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void DeathBehaviour();

	UPROPERTY(EditAnywhere, Category = "Controller Parameters")
	float ControllerLookSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;
	/*UPROPERTY(VisibleAnywhere, Category = "Health")
	bool IsDead;*/
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};
