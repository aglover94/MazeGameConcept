// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create mesh component and set it as the RootComponent
	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	RootComponent = pickupMesh;

	//Set initial value of bIsActive to true
	bIsActive = true;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Function used to return the value of bIsActive
bool APickup::IsActive()
{
	//Return the bIsActive Value (Either true or false)
	return bIsActive;
}

//Function used to set bIsActive to the value of the passed in bool value
void APickup::SetActive(bool pickupState)
{
	//Set bIsActive to the value of pickupState
	bIsActive = pickupState;
}

//Implementation for the WasPickedup function
void APickup::WasPickedup_Implementation()
{
	//Create a new FString variable and set it to the result of GetName
	FString pickupDebugString = GetName();
	//Create a log message to display in the output log in the editor (not needed for final build)
	UE_LOG(LogClass, Log, TEXT("Collected %s"), *pickupDebugString);
}

