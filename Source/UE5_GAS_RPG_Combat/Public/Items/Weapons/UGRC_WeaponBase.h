#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UGRC_WeaponBase.generated.h"

class UBoxComponent;

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AUGRC_WeaponBase();
	
	FOnTargetInteractedDelegate OnWeaponHitTarget;
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;
	
	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult	
	);
	
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex	
	);
	
public:
	FORCEINLINE TObjectPtr<UBoxComponent> GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};