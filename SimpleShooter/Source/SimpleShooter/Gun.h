// Copyright Daniel Newsom 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* GunRoot;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	float MaxRange = 1000.f;
	UPROPERTY(EditAnywhere, Category = "Gun Stats")
	float DamageAmount = 10.f;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* HitSound;

	bool GunTrace(FHitResult &Hit, FVector &HitRotation);
	AController* GetOwnerController() const;
};
