// Copyright - Daniel Newsom 2021


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Check for physics handle
	FindPhysicsHandle();
	FindInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerGrab());
	}
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp,Error,TEXT("No physics handle found on %s"), *GetOwner()->GetName())
	}
}

void UGrabber::FindInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if(Input)
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("No Input component found on %s"), *GetOwner()->GetName())
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();
	
	if(ActorHit)
	{
		if(!PhysicsHandle){return;}
		PhysicsHandle->GrabComponentAtLocation
			(
				ComponentToGrab,
				NAME_None,
				GetPlayerGrab()
			);
	}
}

void UGrabber::Release()
{
	if(!PhysicsHandle){return;}
	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Ray-Cast out to a distance (Reach)
	OUT FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());
	GetWorld()->LineTraceSingleByObjectType
	(
		Hit,
		GetPlayerWorldPosition(),
		GetPlayerGrab(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	
	return Hit;
}

FVector UGrabber::GetPlayerWorldPosition() const
{
	OUT FVector PlayerViewpointLocation;
	OUT FRotator PlayerViewpointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewpointLocation,
		PlayerViewpointRotation
	);

	return PlayerViewpointLocation;
}

FVector UGrabber::GetPlayerGrab() const 
{
	// Get players viewpoint
	OUT FVector PlayerViewpointLocation;
	OUT FRotator PlayerViewpointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewpointLocation,
		PlayerViewpointRotation
	);
	
	// Draw line showing the reach
	return PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;
}
