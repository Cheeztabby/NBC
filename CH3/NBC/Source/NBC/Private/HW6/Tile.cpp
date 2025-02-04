

#include "HW6/Tile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"


ATile::ATile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	// Box Component //
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->AddRelativeLocation(FVector(0, 0, 75.0f));
	BoxComponent->SetRelativeScale3D(FVector(1.5f,1.5f,2.5f));

	// Static Mesh Component //
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Game/LevelPrototyping/Meshes/SM_Cube"));
	if(StaticMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(StaticMesh.Object);
	}
	StaticMeshComponent->SetupAttachment(SceneComponent);
	StaticMeshComponent->AddRelativeLocation(FVector(-50.0f, -50.0f, 0.0f));
	
	// Materials // 
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FindHighlightMaterial(TEXT("/Game/Assets/Materials/Mat_OverlayTile"));
	if(FindHighlightMaterial.Succeeded())
	{
		HighlightMaterialBase = FindHighlightMaterial.Object;		
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FindDefaultMaterial(TEXT("/Engine/OpenWorldTemplate/LandscapeMaterial/MI_ProcGrid"));
	if(FindDefaultMaterial.Succeeded())
	{
		DefaultMaterialBase = FindDefaultMaterial.Object;
	}

	SetActorScale3D(FVector(2.0f,2.0f,0.2f));
	
	// Delegates
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);	
}

void ATile::BeginPlay()
{
	Super::BeginPlay();

	// 특정 확률로 몇개의 타일만 트랩으로 설정
	if(FMath::RandRange(0,100) >= 70)
	{
		if(const UWorld* World = GetWorld())
		{
			FTimerHandle TimerHandle;
			const float Duration = 2.5f;
			const bool bLoop = true;
			World->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::SetTileAsTrap, Duration, bLoop);
		}
	}
}

void ATile::SetTileAsTrap()
{
	bChangeTrap = !bChangeTrap;
	// 트랩은 일정 시간동안 일시적으로 밟으면 떨어지는 트랩으로 바뀜. 구분을 위해 머티리얼 설정
	if(StaticMeshComponent->GetStaticMesh())
	{
		if(bChangeTrap)
		{
			if(HighlightMaterialBase)
			{
				StaticMeshComponent->SetMaterial(0, HighlightMaterialBase);
			}	
		}
		else
		{
			if(DefaultMaterialBase)
			{
				StaticMeshComponent->SetMaterial(0, DefaultMaterialBase);	
			}
		}
	}
}

void ATile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bChangeTrap && OtherActor->IsA(ACharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Display, TEXT("OnOverlapBegin"));
		StaticMeshComponent->SetSimulatePhysics(true);
		StaticMeshComponent->SetEnableGravity(true);
		if(const UWorld* World = GetWorld())
		{
			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, this, &ATile::Destroyed, 3.0f, false);
		}	
	}
}


