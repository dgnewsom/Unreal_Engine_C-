// Copyright - Daniel Newsom 2021


#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}



// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	FindPressurePLate();
	FindAudioComponent();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(TotalMassOfActors() > WeightToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::FindPressurePLate()
{
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no pressure plate assigned!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindAudioComponent()
{
	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!DoorSound)
	{
		UE_LOG(LogTemp,Error,TEXT("%s audio not found!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, OpenSpeed);
	GetOwner()->SetActorRotation(DoorRotation);

	if(!DoorSound){return;}
	if(!OpenDoorSound)
	{
		DoorSound->Play();
		OpenDoorSound = true;
		CloseDoorSound = false;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, CloseSpeed);
	GetOwner()->SetActorRotation(DoorRotation);
	
	if(!DoorSound){return;}
	if(!CloseDoorSound)
	{
		DoorSound->Play();
		CloseDoorSound = true;
		OpenDoorSound = false;
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	if(!PressurePlate){return TotalMass;}

	//Find Overlapping Actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	//Add up their masses
	for (AActor* OverlappingActor : OverlappingActors)
	{
		TotalMass += OverlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}