// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HW6_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NBC_API AHW6_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AHW6_GameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnTiles();
	
	// Rotating Platform // 
	UFUNCTION()
	void SpawnRotatingPlatforms();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Actor Settings|RotatingPlatform", meta=(AllowPrivateAccess=true))
	float RP_MinRandomMoveSpeed = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Actor Settings|RotatingPlatform", meta=(AllowPrivateAccess=true))
	float RP_MaxRandomMoveSpeed = 75.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Actor Settings|RotatingPlatform", meta=(AllowPrivateAccess=true))
	float RP_MinRandomScaleY = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Actor Settings|RotatingPlatform", meta=(AllowPrivateAccess=true))
	float RP_MaxRandomScaleY = 10.0f;

	// Moving Platform //
	UFUNCTION()
	void SpawnMovingPlatforms();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Actor Settings|MovingPlatform", meta=(AllowPrivateAccess=true))
	float MP_MinRandomMoveSpeed = 150.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Actor Settings|MovingPlatform", meta=(AllowPrivateAccess=true))
	float MP_MaxRandomMoveSpeed = 350.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Actor Settings|MovingPlatform", meta=(AllowPrivateAccess=true))
	float MP_MinMoveRange = 800.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Actor Settings|MovingPlatform", meta=(AllowPrivateAccess=true))
	float MP_MaxMoveRange = 1000.0f;
	
	int32 TileCol = 12;
	float TileSpawnSpacing = 330.0f;
};