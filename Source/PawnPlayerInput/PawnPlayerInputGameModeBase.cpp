// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "PawnPlayerInputGameModeBase.h"
#include "PlayerPawn.h"
#include "Runtime\CoreUObject\Public\UObject\ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

APawnPlayerInputGameModeBase::APawnPlayerInputGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/PlayerPawn_BP"));

		if (PlayerPawnBPClass.Class != NULL)
		{
			DefaultPawnClass = PlayerPawnBPClass.Class;
		}

		PrimaryActorTick.bCanEverTick = true;
}

void APawnPlayerInputGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Call the function to set the current state to playing
	SetCurrentState(EPlayState::EPlaying);

	APlayerPawn* MyCharacter = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Check that MyCharacter is true
	if (MyCharacter)
	{
		//If it is then set the collectNumToWin variable to the initialCollectNum value plus 4
		collectNumToWin = (MyCharacter->GetInitialCollectNum()) + 4.0f;
	}

	//Check that HudWidgetClass doesn't equal nullptr
	if (HUDWidgetClass != nullptr)
	{
		//If it doesn't then create a widget using the HUDWidgetClass
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		//Check that currentWidget doesn't equal nullptr
		if (currentWidget != nullptr)
		{
			//If it doesn't then add the currentWidget to the viewPort
			currentWidget->AddToViewport();
		}
	}
}

void APawnPlayerInputGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerPawn* MyCharacter = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Check if MyCharacter is true
	if (MyCharacter)
	{
		//If it is then check if the currentCollectNum value equals the collectNumToWin value
		if (MyCharacter->GetCurrentCollectNum() == collectNumToWin)
		{
			//If it does then call the SetCurrentStateFunction passing in the EWon state
			SetCurrentState(EPlayState::EWon);
		}
	}
}

//Function used to return the value of CollectNumToWin
float APawnPlayerInputGameModeBase::GetCollectNumToWin() const
{
	//Return the collectNumToWin value
	return collectNumToWin;
}

//Function to return the currentState of the game
EPlayState APawnPlayerInputGameModeBase::GetCurrentState() const
{
	//Return the currentState value
	return currentState;
}

//Function used to set the currentState value to the value of newState
void APawnPlayerInputGameModeBase::SetCurrentState(EPlayState newState)
{
	//Set current state
	currentState = newState;

	//Handle the new state change
	HandleStateChange(newState);
}

//Function to handle what should happen when the play state is changed
void APawnPlayerInputGameModeBase::HandleStateChange(EPlayState newState)
{
	switch (newState)
	{
		//Game is playing
		case EPlayState::EPlaying:
		{
			//Do this for when the game is playing
		}
		break;

		//If the game has been won
		case EPlayState::EWon:
		{
			//Do this for when the game has been won

			//Block input
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

			if (PlayerController)
			{
				PlayerController->SetCinematicMode(true, false, false, true, true);
			}
		}
		break;

		//Unknown default case
		default:
		case EPlayState::EUnknown:
		{
			//Do nothing
		}
		break;

	}
}


