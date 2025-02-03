#include "MyActor.h"

#include "Elements/Columns/TypedElementAlertColumns.h"

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	Move();
}

void AMyActor::Move()
{
	float AccDistance = 0.0f;
	int32 EventCount = 0;
	FVector2D CurrentLocation = Start;
	// 문제 조건: Move 함수는 10회 움직이면서 움직일때마다 좌표를 출력
	for(int32 i = 0; i<10; ++i)
	{
		const FVector2D NextStep = FVector2D(Step(),Step());
		AccDistance += Distance(CurrentLocation, CurrentLocation + NextStep);
		UE_LOG(LogTemp, Display, TEXT("이동 거리: %f"), Distance(CurrentLocation, CurrentLocation + NextStep));
		CurrentLocation += NextStep;
		UE_LOG(LogTemp, Warning, TEXT("도착한 좌표: (%f, %f)"),CurrentLocation.X,CurrentLocation.Y);
		if(CreateEvent())
		{
			UE_LOG(LogTemp, Warning, TEXT("이벤트 발생"));
			EventCount++;
		}
	}
	// 10회 이동후 총 이동 거리와 총 이벤트 발생 횟수 출력
	UE_LOG(LogTemp, Warning, TEXT("총 이동 거리: %f"), AccDistance);
	UE_LOG(LogTemp, Warning, TEXT("총 이벤트 발생 횟수: %d"), EventCount);
}

int32 AMyActor::Step()
{
	// 문제 조건: Step 함수는 0 혹은 1은 랜덤으로 반환
	return FMath::RandRange(0,1);
}

float AMyActor::Distance(const FVector2D First, const FVector2D Second)
{
	return FMath::Sqrt(FMath::Pow(Second.X - First.X,2) + FMath::Pow(Second.Y - First.Y,2));
}

int32 AMyActor::CreateEvent()
{
	// 문제 조건: 10회 이동시 각 스텝마다 50% 확률로 랜덤하게 이벤트가 발생
	return FMath::RandRange(0,1);
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

