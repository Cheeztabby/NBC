#include "HW8/Actor/MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AMineItem::AMineItem()
{
	
}

void AMineItem::ActivateItem(AActor* Activator)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::Explode, ExplosionDelay, false);
}

void AMineItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->SetSphereRadius(ExplosionRadius);
}

void AMineItem::Explode()
{
	TArray<AActor*> OverlappingActors;
	SphereComponent->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if (IsPlayer(Actor))
		{
			UGameplayStatics::ApplyDamage(Actor, ExplosionDamage, nullptr, this, UDamageType::StaticClass());
		}
	}
	DestroyItem();
}
