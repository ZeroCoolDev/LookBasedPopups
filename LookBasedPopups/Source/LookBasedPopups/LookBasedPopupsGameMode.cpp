// Copyright Epic Games, Inc. All Rights Reserved.

#include "LookBasedPopupsGameMode.h"
#include "LookBasedPopupsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALookBasedPopupsGameMode::ALookBasedPopupsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
