// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HW8_GameInstance.generated.h"

UCLASS()
class NBC_API UHW8_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UHW8_GameInstance();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="GameData")
	int32 TotalScore = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="GameData")
	int32 CurrentLevelIndex = 0;

	UFUNCTION(BlueprintCallable, Category="GameData")
	void AddToScore(const int32 Amount);
};
