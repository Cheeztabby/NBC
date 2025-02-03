#include "RotatingPlatform.h"

// Sets default values
ARotatingPlatform::ARotatingPlatform(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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
	SetActorScale3D(FVector(1.0f,5.0f,1.0f)); // 뛰어 넘을 수 있게 Z Scale을 1.0f 미만으로 두는 것이 좋아보임
}

void ARotatingPlatform::SetRotationSpeed(const float InRotationSpeed)
{
	RotationSpeed = InRotationSpeed;
}

void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f,DeltaTime * RotationSpeed, 0.0f));	
	}
}

