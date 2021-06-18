// Copyright Daniel Newsom 2021


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Root"));
	SetRootComponent(GunRoot);
	
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Gun Mesh");
	GunMesh->SetupAttachment(GunRoot);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn){return;}
	AController* OwnerController = OwnerPawn->GetController();
	if(!OwnerController){return;}
	FRotator PlayerViewRotation;
	FVector	PlayerViewLocation;
	OwnerController->GetPlayerViewPoint(PlayerViewLocation,PlayerViewRotation);

	FVector End = PlayerViewLocation + PlayerViewRotation.Vector() * MaxRange;
	//LineTrace TODO
	FHitResult Hit;
	bool bSuccessful = GetWorld()->LineTraceSingleByChannel(Hit,PlayerViewLocation,End,ECC_GameTraceChannel1);
	if(bSuccessful)
	{
		FVector ShotDirection = -PlayerViewRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitEffect,Hit.Location,ShotDirection.Rotation());
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

