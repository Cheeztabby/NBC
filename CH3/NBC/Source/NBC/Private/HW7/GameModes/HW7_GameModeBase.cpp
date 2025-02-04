// Fill out your copyright notice in the Description page of Project Settings.


#include "HW7/GameModes/HW7_GameModeBase.h"
#include "HW7/PlayerPawn.h"

AHW7_GameModeBase::AHW7_GameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/HW7/Blueprints/BP_PlayerPawn_C"));
	if(PlayerPawn.Succeeded())
	{
		DefaultPawnClass = PlayerPawn.Class;
	}
}
