// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PawnPlayerInputGameModeBase.generated.h"

/**
 * 
 */
//Enum to store state of gameplay
UENUM(BlueprintType)
enum class EPlayState : uint8
{
	EPlaying,
	EWon,
	EUnknown
};

UCLASS()
class PAWNPLAYERINPUT_API APawnPlayerInputGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APawnPlayerInputGameModeBase();

	virtual void Tick(float DeltaTime) override;

	//Function to return the value of CollectNumToWin
	UFUNCTION(BlueprintPure, Category = "Collection")
		float GetCollectNumToWin() const;

	virtual void BeginPlay() override;

	//Returns the current playing state
	UFUNCTION(BlueprintPure, Category = "Collection")
	EPlayState GetCurrentState() const;

	//Set the current playing state
	void SetCurrentState(EPlayState newState);

protected:
	//New float variable used to see if the player has collected enough to win the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collection", Meta = (BlueprintProtected = "true"))
		float collectNumToWin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collection", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* currentWidget;

private:
	//Keep track of play state
	EPlayState currentState;

	//Handle any function calls that rely on changing the playing state
	void HandleStateChange(EPlayState newState);
};
