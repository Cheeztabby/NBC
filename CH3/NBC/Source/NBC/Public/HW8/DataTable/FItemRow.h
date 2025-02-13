#pragma once

#include "CoreMinimal.h"
#include "FItemRow.generated.h"

USTRUCT(BlueprintType)
struct FItemRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
	//TSoftClassPtr<AActor> ItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance; 
};
