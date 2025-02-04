// Fill out your copyright notice in the Description page of Project Settings.


#include "HW6/GameModes/HW6_GameModeBase.h"
#include "HW6/MovingPlatform.h"
#include "HW6/RotatingPlatform.h"
#include "HW6/Tile.h"

AHW6_GameModeBase::AHW6_GameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if(PlayerPawn.Succeeded())
	{
		DefaultPawnClass = PlayerPawn.Class;
	}
}

void AHW6_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnTiles();
	SpawnRotatingPlatforms();
	SpawnMovingPlatforms();
}

void AHW6_GameModeBase::SpawnTiles()
{
	if(UWorld* World = GetWorld())
	{
		const FVector StartLocation = FVector(0.0f, 0.0f, 0.0f);
		for(int32 i = 0; i < TileCol; ++i)
		{
			for(int32 j = 0; j < 5; ++j)
			{
				FActorSpawnParameters SpawnParameters;
				const FVector SpawnLocation = StartLocation - FVector(i * TileSpawnSpacing, j * TileSpawnSpacing, 0.0f);
				World->SpawnActor<ATile>(ATile::StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
			}
		}
	}
}

void AHW6_GameModeBase::SpawnRotatingPlatforms()
{
	if(UWorld* World = GetWorld())
	{
		const FVector StartLocation = FVector(-500.0f, 0.0f, 0.0f);
		const float SpawnSpacing = 1500.0f;
		for(int32 i = 0; i < 3; ++i)
		{
			FActorSpawnParameters SpawnParameters;
			const FVector SpawnLocation = StartLocation - FVector(i * SpawnSpacing, 0.0f, 0.0f);
			ARotatingPlatform* RotatingPlatform = World->SpawnActor<ARotatingPlatform>(ARotatingPlatform::StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
			RotatingPlatform->SetActorScale3D(RotatingPlatform->GetActorScale3D() + FVector(0.0f, FMath::RandRange(RP_MinRandomScaleY, RP_MaxRandomScaleY), 0.0f));
			RotatingPlatform->SetRotationSpeed(FMath::RandRange(RP_MinRandomMoveSpeed,RP_MaxRandomMoveSpeed));
		}
	}
}

void AHW6_GameModeBase::SpawnMovingPlatforms()
{
	if(UWorld* World = GetWorld())
	{
		const FVector StartLocation = FVector(-50.0f, -500.0f, 10.0f);
		// 타일 간격과 맞춰 사용할 것이므로 Tile과 동일한 변수(TileCol, TileSpawnSpacing) 사용
		for(int32 i = 0; i < TileCol; ++i)
		{
			if(i % 3 == 0)
			{
				FActorSpawnParameters SpawnParameters;
				const FVector SpawnLocation = StartLocation - FVector(i * TileSpawnSpacing, 0.0f, 0.0f);
				AMovingPlatform* MovingPlatform = World->SpawnActor<AMovingPlatform>(AMovingPlatform::StaticClass(), SpawnLocation, FRotator::ZeroRotator, SpawnParameters);
				MovingPlatform->SetMoveSpeed(FMath::RandRange(MP_MinRandomMoveSpeed, MP_MaxRandomMoveSpeed));
				MovingPlatform->SetMaxRange(FMath::RandRange(MP_MinMoveRange, MP_MaxMoveRange));	
			}
		}
	}
}
