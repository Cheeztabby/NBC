#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "MineItem.generated.h"

UCLASS()
class NBC_API AMineItem : public AItemBase
{
	GENERATED_BODY()

public:
	AMineItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;

	virtual void PostInitializeComponents() override;
private:
	void Explode();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionDelay = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float ExplosionRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage = 0.0f;
};
