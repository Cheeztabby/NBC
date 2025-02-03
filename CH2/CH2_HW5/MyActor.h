#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class NBC_HW5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyActor();
    virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Move();

	UFUNCTION()
	int32 Step();

	UFUNCTION()
	float Distance(FVector2D First, FVector2D Second);

	UFUNCTION()
	int32 CreateEvent();
	
	UPROPERTY()
	FVector2D Start = FVector2D::ZeroVector;

};
