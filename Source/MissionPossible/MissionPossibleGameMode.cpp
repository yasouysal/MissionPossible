// Copyright Epic Games, Inc. All Rights Reserved.

#include "MissionPossibleGameMode.h"
#include "MissionPossibleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMissionPossibleGameMode::AMissionPossibleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
