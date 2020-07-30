// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "MeshWidgetExampleGameMode.h"
#include "MeshWidgetExample.h"
#include "MeshWidgetExamplePlayerController.h"
#include "MeshWidgetExampleCharacter.h"

AMeshWidgetExampleGameMode::AMeshWidgetExampleGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMeshWidgetExamplePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}