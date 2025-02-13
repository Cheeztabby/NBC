#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class NBC_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ASpawnVolume();

	UFUNCTION(BlueprintCallable, Category="SpawnVolume")
	AActor* SpawnRandomItem() const;

	AActor* SpawnItem(const TSubclassOf<AActor>& ItemClass) const;
protected:
	
	FVector GetRandomPointInVolume() const;

	FItemRow* GetRandomItem() const;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SpawnVolume")
	UDataTable* ItemDataTable = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnVolume")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpawnVolume")
	UBoxComponent* BoxComponent;
};
