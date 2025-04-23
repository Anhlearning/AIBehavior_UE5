// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIBehaviorGameMode.h"
#include "AIBehaviorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIBehaviorGameMode::AAIBehaviorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
