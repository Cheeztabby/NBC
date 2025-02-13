#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HW8/Interface/ItemInterface.h"
#include "ItemBase.generated.h"

class USphereComponent;

UCLASS()
class NBC_API AItemBase : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	AItemBase();

	virtual void DestroyItem() override;
protected:
	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	
	virtual void ActivateItem(AActor* Activator) override;

	virtual EItemType GetItemType() const override;

	bool IsPlayer(const AActor* Activator) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Tag")
	FName CompareTag = FName("Player");
};
