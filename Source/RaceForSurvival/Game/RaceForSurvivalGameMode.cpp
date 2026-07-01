// Copyright Epic Games, Inc. All Rights Reserved.

#include "RaceForSurvivalGameMode.h"
#include "RaceForSurvival/Character/RaceForSurvivalCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARaceForSurvivalGameMode::ARaceForSurvivalGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/RaceForSurvival/Character/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
