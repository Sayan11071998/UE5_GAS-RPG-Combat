#include "Items/PickUps/UGRC_PickUpBase.h"
#include "Components/SphereComponent.h"

AUGRC_PickUpBase::AUGRC_PickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PickUpCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollisionSphere"));
	SetRootComponent(PickUpCollisionSphere);
	PickUpCollisionSphere->InitSphereRadius(50.f);
	PickUpCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AUGRC_PickUpBase::OnPickUpCollisionSphereBeginOverlap);
}

void AUGRC_PickUpBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}