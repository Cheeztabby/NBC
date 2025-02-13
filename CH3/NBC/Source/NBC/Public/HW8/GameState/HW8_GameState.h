// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "HW8_GameState.generated.h"

/**
 * 
 */
UCLASS()
class NBC_API AHW8_GameState : public AGameState
{
	GENERATED_BODY()

public:
	AHW8_GameState();

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(const int32 Amount);

	void OnCoinCollected();

	void UpdateHUD() const;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Level")
	void StartLevel();

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	void OnLevelTimeUp();

	void EndLevel();

	UFUNCTION(BlueprintCallable, Category = "Level")
	void StartWave();

	void UpdateWave();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<int32> ItemToSpawns;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<float> LevelDurations;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

	FTimerHandle LevelTimerHandle;
	
	FTimerHandle HUDUpdateTimerHandle;

	bool bIsWaveVersion = true;
};
