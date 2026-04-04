#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/UGRC_HeroGameplayAbility.h"
#include "UGRC_HeroAbility_TargetLock.generated.h"

class UUGRC_WidgetBase;

UCLASS()
class UE5_GAS_RPG_COMBAT_API UUGRC_HeroAbility_TargetLock : public UUGRC_HeroGameplayAbility
{
	GENERATED_BODY()
	
protected:
	// ~ Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// ~ End UGameplayAbility Interface
	
private:
	void TryLockOnTarget();
	void GetAvailableActorsToLock();
	TObjectPtr<AActor> GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();
	void CancelTargetLockAbility();
	void Cleanup();
	
	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	float BoxTraceDistance = 5000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	FVector TraceBoxSize = FVector(5000.f, 5000.f, 300.f);
	
	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;
	
	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	bool bShowPersistentDebugShape = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "TargetLock")
	TSubclassOf<UUGRC_WidgetBase> TargetLockWidgetClass;
	
	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentLockedActor;
	
	UPROPERTY()
	TObjectPtr<UUGRC_WidgetBase> DrawnTargetLockWidget;
	
	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;
};