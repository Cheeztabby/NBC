#include "HW7/GameModes/HW7_GameModeBase.h"
AHW7_GameModeBase::AHW7_GameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/HW7/Blueprints/BP_PlayerPawn_C"));
	if(PlayerPawn.Succeeded())
	{
		DefaultPawnClass = PlayerPawn.Class;
	}
}
