#include "HW8/Actor/CoinItem.h"
#include "HW8/GameState/HW8_GameState.h"

ACoinItem::ACoinItem()
{
}

void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	if (IsPlayer(Activator))
	{
		if(const UWorld* World = GetWorld())
		{
			if(AHW8_GameState* GameState = World->GetGameState<AHW8_GameState>())
			{
				GameState->AddScore(PointValue);
				GameState->OnCoinCollected();
			}
		}
		DestroyItem();
	}
}
