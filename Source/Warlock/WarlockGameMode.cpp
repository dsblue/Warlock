// Copyright Epic Games, Inc. All Rights Reserved.

#include "WarlockGameMode.h"
#include "WarlockCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWarlockGameMode::AWarlockGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
