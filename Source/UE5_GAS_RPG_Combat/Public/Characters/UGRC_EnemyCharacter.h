#pragma once

#include "CoreMinimal.h"
#include "Characters/UGRC_BaseCharacter.h"
#include "UGRC_EnemyCharacter.generated.h"

class UBoxComponent;
class UWidgetComponent;
class UUGRC_EnemyCombatComponent;
class UUGRC_EnemyUIComponent;

UCLASS()
class UE5_GAS_RPG_COMBAT_API AUGRC_EnemyCharacter : public AUGRC_BaseCharacter
{
	GENERATED_BODY()
	
public:
	AUGRC_EnemyCharacter();
	
	// ~ Begin IUGRC_PawnCombatInterface Interface
	virtual TObjectPtr<UUGRC_PawnCombatComponent> GetPawnCombatComponent() const override;
	// ~ End IUGRC_PawnCombatInterface Interface
	
	// ~ Begin IUGRC_PawnUIInterface Interface
	virtual TObjectPtr<UUGRC_PawnUIComponent> GetPawnUIComponent() const override;
	virtual TObjectPtr<UUGRC_EnemyUIComponent> GetEnemyUIComponent() const override;
	// ~ End IUGRC_PawnUIInterface Interface
	
protected:
	virtual void BeginPlay() override;
	
	// ~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	// ~ End APawn Interface
	
#if WITH_EDITOR
	// ~ Begin UObject Interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// ~ End UObject Interface
#endif
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UUGRC_EnemyCombatComponent> EnemyCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UBoxComponent> LeftHandCollisionBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName LeftHandCollisionBoxAttachBoneName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UBoxComponent> RightHandCollisionBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName RightHandCollisionBoxAttachBoneName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUGRC_EnemyUIComponent> EnemyUIComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;
	
	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult	
	);
	
private:
	void InitEnemyStartupData();
	
public:
	FORCEINLINE TObjectPtr<UUGRC_EnemyCombatComponent> GetEnemyCombatComponent() const { return EnemyCombatComponent; }
	FORCEINLINE TObjectPtr<UBoxComponent> GetLeftHandCollisionBox() const { return LeftHandCollisionBox; }
	FORCEINLINE TObjectPtr<UBoxComponent> GetRightHandCollisionBox() const { return RightHandCollisionBox; }
};