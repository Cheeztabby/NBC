#include "HW8/Actor/HealingItem.h"

#include "HW8/Character/HW8_Character.h"

AHealingItem::AHealingItem()
{
	
}


void AHealingItem::BeginPlay()
{
	Super::BeginPlay();
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	if(IsPlayer(Activator))
	{
		if(AHW8_Character* PlayerCharacter = Cast<AHW8_Character>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}
		DestroyItem();	
	}
}

