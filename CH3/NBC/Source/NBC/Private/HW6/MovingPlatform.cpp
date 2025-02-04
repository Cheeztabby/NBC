#include "HW6/MovingPlatform.h"

AMovingPlatform::AMovingPlatform(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube"));
	if(StaticMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(StaticMesh.Object);
	}
}

void AMovingPlatform::SetMoveSpeed(const float InMoveSpeed)
{
	MoveSpeed = InMoveSpeed;
}

void AMovingPlatform::SetMaxRange(const float InMaxRange)
{
	MaxRange = InMaxRange;
	MaxRangeSquared = FMath::Square(InMaxRange);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if(FVector::Dist(StartLocation, GetActorLocation()) >= MaxRange)
	if(FVector::DistSquared(StartLocation, GetActorLocation()) >= MaxRangeSquared)
	{
		bSwitchDirection = !bSwitchDirection;	
	}
	float AddOffset = MoveSpeed * DeltaTime;
	if(bSwitchDirection)
	{
		AddOffset *= -1.0f;
	}
	AddActorLocalOffset(FVector(0.0f,AddOffset,0.0f), true);	
}