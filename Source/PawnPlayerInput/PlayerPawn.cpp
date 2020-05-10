// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Pickup.h"
#include "InheritedPickup.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Create the components
	sphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("Sphere Mesh");
	springArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	sphereCollection = CreateDefaultSubobject<USphereComponent>("Collection Sphere");

	//Set the root component to be the sphere mesh
	RootComponent = sphereMesh;
	//Attach the spring arm to the mesh, then the camera to the spring arm
	springArm->SetupAttachment(sphereMesh);
	camera->SetupAttachment(springArm);
	
	sphereCollection->SetupAttachment(sphereMesh);
	sphereCollection->SetSphereRadius(75.0f);


	//Enable physics to the mesh
	sphereMesh->SetSimulatePhysics(true);
	moveForce = 100000;

	//Set base collection number
	initialCollectNum = 0.0f;
	currentCollectNum = initialCollectNum;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind the MoveUp and MoveRight functions to the MoveUp/MoveRight axis events
	InputComponent->BindAxis("MoveUp", this, &APlayerPawn::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);

	//Bind the CollectPickups function to the Collect action when the button is pressed 
	InputComponent->BindAction("Collect", IE_Pressed, this, &APlayerPawn::CollectPickups);
}

//Called to collect the pickups
void APlayerPawn::CollectPickups()
{
	//Get all overlapping actors and store them in an array
	TArray<AActor*> CollectedActors;
	sphereCollection->GetOverlappingActors(CollectedActors);

	//Variable to track collectNum
	float collectedNum = 0;

	//Loop through the collectedActors array
	for (int32 i = 0; i < CollectedActors.Num(); i++)
	{
		//Cast actor to APickup
		APickup* const testPickup = Cast<APickup>(CollectedActors[i]);

		//If the cast is successful and the pickup is active
		if (testPickup && !testPickup->IsPendingKill() && testPickup->IsActive())
		{
			//Call the pickup WasPickedup function
			testPickup->WasPickedup();
			
			//Check to see if pickup is also an inheritedPickup
			AInheritedPickup* const testInheritedPickup = Cast<AInheritedPickup>(testPickup);
			if (testInheritedPickup)
			{
				//Increase the collectedNum
				collectedNum += testInheritedPickup->GetCollectNumber();
			}

			//Deactivate pickup
			testPickup->SetActive(false);
		}
	}

	//Check if the collectedNum value is more than 0
	if (collectedNum > 0)
	{
		//If it is then call the function passing in the collectedNum value
		UpdateCollectNum(collectedNum);
	}
}

//Function called when moving the pawn up or down
void APlayerPawn::MoveUp(float value)
{
	//Create an FVector variable and set it to the vector values
	//multiplied by moveForce value then multiplied by value
	FVector forceToAdd = FVector(1, 0, 0) * moveForce * value;
	//Call the AddForce function passing in the FVector variable
	sphereMesh->AddForce(forceToAdd);
}

//Function called when moving the pawn left or right
void APlayerPawn::MoveRight(float value)
{
	//Create an FVector variable and set it to the vector values
	//multiplied by moveForce value then multiplied by value
	FVector forceToAdd = FVector(0, 1, 0) * moveForce * value;
	//Call the AddForce function passing in the FVector variable
	sphereMesh->AddForce(forceToAdd);
}

//Function used to return the number of collectibles initially set
float APlayerPawn::GetInitialCollectNum()
{
	//Return the initialCollectNum value
	return initialCollectNum;
}

//Function used to retun the current number collected
float APlayerPawn::GetCurrentCollectNum()
{
	//Return the currecntCollectNum value
	return currentCollectNum;
}

//Called when collecting a pickup
void APlayerPawn::UpdateCollectNum(float collectionChange)
{
	//Add the collectionChange value to the value of currentCollectNum
	currentCollectNum += collectionChange;
}

