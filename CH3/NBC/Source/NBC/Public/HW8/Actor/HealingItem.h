#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "HealingItem.generated.h"

UCLASS()
class NBC_API AHealingItem : public AItemBase
{
	GENERATED_BODY()

public:
	AHealingItem();

protected:
	virtual void BeginPlay() override;

	virtual void ActivateItem(AActor* Activator) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount = 0;
};
