// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeshWidgetExampleGameMode.h"
#include "MeshWidgetExamplePlayerController.h"
#include "MeshWidgetExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

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