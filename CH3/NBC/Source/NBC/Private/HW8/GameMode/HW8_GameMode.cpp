#include "HW8/GameMode/HW8_GameMode.h"
#include "HW8/GameState/HW8_GameState.h"

AHW8_GameMode::AHW8_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> BPPlayerPawn(TEXT("/Game/HW8/Blueprints/BP_HW8_Character"));
	if(BPPlayerPawn.Succeeded())
	{
		DefaultPawnClass = BPPlayerPawn.Class;
	}
	GameStateClass = AHW8_GameState::StaticClass();
}
