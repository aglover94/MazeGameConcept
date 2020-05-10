// Fill out your copyright notice in the Description page of Project Settings.


#include "InheritedPickup.h"

AInheritedPickup::AInheritedPickup()
{
	//Set the SimulatePhysics to true
	GetMesh()->SetSimulatePhysics(true);

	//Set the collectionNumber variable to 1
	collectionNumber = 1.0f;
}

void AInheritedPickup::WasPickedup_Implementation()
{
	//Use base pickup behaviour
	Super::WasPickedup_Implementation();

	//Destroy object
	Destroy();
}

//Function used to return the collectionNumber value
float AInheritedPickup::GetCollectNumber()
{
	//Return the collectionNumber value
	return collectionNumber;
}
