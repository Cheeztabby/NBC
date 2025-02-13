// Fill out your copyright notice in the Description page of Project Settings.


#include "HW8/GameInstance/HW8_GameInstance.h"

UHW8_GameInstance::UHW8_GameInstance()
{
}

void UHW8_GameInstance::AddToScore(const int32 Amount)
{
	TotalScore += Amount;
}
