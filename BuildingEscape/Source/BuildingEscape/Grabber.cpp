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
		// Get players viewpoint
	OUT FVector PlayerViewpointLocation;
	OUT FRotator PlayerViewpointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewpointLocation,
		PlayerViewpointRotation
	);
	
	// Draw line showing the reach
	FVector LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle)
	{
		UE_LOG(LogTemp,Warning,TEXT("Physics handle found on %s"), *GetOwner()->GetName())
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("No physics handle found on %s"), *GetOwner()->GetName())
	}
}

void UGrabber::FindInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if(Input)
	{
		//UE_LOG(LogTemp,Warning,TEXT("Input component found on %s"), *GetOwner()->GetName())
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
	// Get players viewpoint
	OUT FVector PlayerViewpointLocation;
	OUT FRotator PlayerViewpointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewpointLocation,
		PlayerViewpointRotation
	);
	
	// Draw line showing the reach
	FVector LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;
	
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	if(HitResult.GetActor())
	{
		UE_LOG(LogTemp,Warning,TEXT("Grabbed %s"), *HitResult.GetActor()->GetName());
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab,NAME_None,LineTraceEnd);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Grabber Pressed"));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp,Warning,TEXT("Grabber Released"));
	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get players viewpoint
	OUT FVector PlayerViewpointLocation;
	OUT FRotator PlayerViewpointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewpointLocation,
		PlayerViewpointRotation
	);
	
	// Draw line showing the reach
	FVector LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;
		
	// Ray-Cast out to a distance (Reach)
	OUT FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());
	GetWorld()->LineTraceSingleByObjectType
	(
		Hit,
		PlayerViewpointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}



