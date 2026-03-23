#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UGRC_WeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AUGRC_WeaponBase();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;
	
public:
	FORCEINLINE TObjectPtr<UBoxComponent> GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};