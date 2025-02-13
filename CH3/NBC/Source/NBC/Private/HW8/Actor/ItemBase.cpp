#include "HW8/Actor/ItemBase.h"
#include "Components/SphereComponent.h"

AItemBase::AItemBase()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereComponent->SetupAttachment(SceneComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(SphereComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnItemOverlap);

}

void AItemBase::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPlayer(OtherActor))
	{
		ActivateItem(OtherActor);
	}
}

void AItemBase::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AItemBase::ActivateItem(AActor* Activator)
{
	
}

EItemType AItemBase::GetItemType() const
{
	return ItemType;
}

void AItemBase::DestroyItem()
{
	Destroy();
}

bool AItemBase::IsPlayer(const AActor* Activator) const 
{
	return (Activator && Activator->ActorHasTag(CompareTag));
}


