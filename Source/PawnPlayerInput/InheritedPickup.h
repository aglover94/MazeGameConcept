// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "InheritedPickup.generated.h"

/**
 * 
 */
UCLASS()
class PAWNPLAYERINPUT_API AInheritedPickup : public APickup
{
	GENERATED_BODY()

public:
	//Set default values for the properties
	AInheritedPickup();

	//Override WasPickedup function, use Implementation because of it being a BlueprintNativeEvent
	void WasPickedup_Implementation() override;

	//Public way to access the collection number
	float GetCollectNumber();

protected:
	//Set the number of collected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collection", Meta = (BlueprintProtected = "true"))
		float collectionNumber;
};
