#include "HW8/Actor/SpawnVolume.h"

#include "Components/BoxComponent.h"
#include "HW8/DataTable/FItemRow.h"

ASpawnVolume::ASpawnVolume()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBoxArea"));
	BoxComponent->SetupAttachment(RootComponent);
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	const FVector BoxExtent = BoxComponent->GetScaledBoxExtent();
	const FVector BoxCenterLocation = BoxComponent->GetComponentLocation();

	const float RandX = FMath::FRandRange(-BoxExtent.X, BoxExtent.X);
	const float RandY = FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y);
	
	const FVector AddRandomLocation = FVector(RandX, RandY, BoxCenterLocation.Z - 200.0f);
	
	return BoxCenterLocation + AddRandomLocation;
}

AActor* ASpawnVolume::SpawnItem(const TSubclassOf<AActor>& ItemClass) const
{
	if(!ItemClass)
	{
		return nullptr;
	}
	return GetWorld()->SpawnActor<AActor>(ItemClass, GetRandomPointInVolume(), FRotator::ZeroRotator);
}

FItemRow* ASpawnVolume::GetRandomItem() const
{
	if(!ItemDataTable)
	{
		return nullptr;
	}
	TArray<FItemRow*> ItemRows;
	static const FString ContextString(TEXT("ItemContext"));
	ItemDataTable->GetAllRows(ContextString,ItemRows);

	if(ItemRows.IsEmpty())
	{
		return nullptr;
	}

	// 누적 랜덤 확률 뽑기 알고리즘
	float TotalChance = 0.0f;
	for(const FItemRow* ItemRow : ItemRows)
	{
		if(ItemRow)
		{
			TotalChance += ItemRow->SpawnChance;
		}
	}
	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;

	for(FItemRow* ItemRow : ItemRows)
	{
		AccumulateChance += ItemRow->SpawnChance;
		if(RandValue <= AccumulateChance)
		{
			return ItemRow;
		}
	}
	return nullptr;
}

AActor* ASpawnVolume::SpawnRandomItem() const
{
	if(const FItemRow* SelectedRow = GetRandomItem())
	{
		if(UClass* SelectedRowClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(SelectedRowClass);
		}
	}
	return nullptr;
}

