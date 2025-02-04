#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class UInterpToMovementComponent;

UCLASS()
class NBC_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION()
	void SetMoveSpeed(const float InMoveSpeed);

	UFUNCTION()
	void SetMaxRange(const float InMaxRange);
private:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Platform Settings", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Platform Settings", meta = (AllowPrivateAccess = "true"))
	float MaxRange = 180.0f;
	
	float MaxRangeSquared = FMath::Square(MaxRange);	

	FVector StartLocation = FVector::ZeroVector;

	bool bSwitchDirection = true;
	
};
