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
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	
	bool bSuccessful = GunTrace(Hit,ShotDirection);
	
	if(bSuccessful)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitEffect,Hit.Location,ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),HitSound,Hit.Location,ShotDirection.Rotation());
		
		AActor* HitActor = Hit.GetActor();
		if(HitActor != nullptr)
		{
			AController * OwnerController = GetOwnerController();
			if(OwnerController == nullptr){return;}
			FPointDamageEvent DamageEvent(DamageAmount, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(DamageAmount,DamageEvent,OwnerController,this);
		}
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

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController * OwnerController = GetOwnerController();
	if(OwnerController == nullptr){return false;}
	FRotator PlayerViewRotation;
	FVector	PlayerViewLocation;
	OwnerController->GetPlayerViewPoint(PlayerViewLocation,PlayerViewRotation);
	ShotDirection = -PlayerViewRotation.Vector();
	FVector End = PlayerViewLocation + PlayerViewRotation.Vector() * MaxRange;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit,PlayerViewLocation,End,ECC_GameTraceChannel1,Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr){return nullptr;}
	return OwnerPawn->GetController();
}


