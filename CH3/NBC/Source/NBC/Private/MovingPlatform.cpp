#include "MovingPlatform.h"

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
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(FVector::Dist(StartLocation, GetActorLocation()) >= MaxRange)
	{
		bSwitchDirection = !bSwitchDirection;	
	}
	float SwitchSign = 1.0f;
	if(bSwitchDirection)
	{
		SwitchSign = -1.0f;
	}
	AddActorLocalOffset(FVector(0.0f,SwitchSign * MoveSpeed * DeltaTime,0.0f), true);	
}

