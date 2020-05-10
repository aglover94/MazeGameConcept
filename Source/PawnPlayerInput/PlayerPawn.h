// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerPawn.generated.h"

UCLASS()
class PAWNPLAYERINPUT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Function used to collect the pickups
	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void CollectPickups();

	//The starting collection number
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collection")
	float initialCollectNum;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//The mesh for the pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* sphereMesh;
	
	//The spring arm that will be attached to the mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* springArm;
	
	//The camera that will be attached to the spring arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* camera;
	
	//A sphere component used to see if player is in contact with a pickup
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* sphereCollection;
	
	//Variable to determine the amount of force to add to the movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float moveForce;

	//Functions to move the pawn based on the passed in values
	void MoveUp(float value);
	void MoveRight(float value);

	FORCEINLINE USphereComponent* GetSphereCollection() const { return sphereCollection; }

	//Accessor function for initialCollectNum
	UFUNCTION(BlueprintPure, Category = "Collection")
		float GetInitialCollectNum();

	//Accessor function for currentCollectNum
	UFUNCTION(BlueprintPure, Category = "Collection")
		float GetCurrentCollectNum();

	//Function to update currentCollectNum
	UFUNCTION(BlueprintCallable, Category = "Collection")
		void UpdateCollectNum(float collectionChange);

private:
	//Current collection number
	UPROPERTY(VisibleAnywhere, Category = "Collection")
	float currentCollectNum;
};
