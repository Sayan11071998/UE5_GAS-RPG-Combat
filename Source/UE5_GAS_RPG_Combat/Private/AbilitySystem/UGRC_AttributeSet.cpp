#include "AbilitySystem/UGRC_AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "UGRC_FunctionLibrary.h"
#include "UGRC_GameplayTags.h"
#include "Interfaces/UGRC_PawnUIInterface.h"
#include "Components/UI/UGRC_PawnUIComponent.h"
#include "Components/UI/UGRC_HeroUIComponent.h"

#include "UGRC_DebugHelper.h"

UUGRC_AttributeSet::UUGRC_AttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UUGRC_AttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IUGRC_PawnUIInterface>(Data.Target.GetAvatarActor());
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s did not implement IUGRC_PawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	UUGRC_PawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	checkf(PawnUIComponent, TEXT("Cound not extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
		
		if (UUGRC_HeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		
		SetCurrentHealth(NewCurrentHealth);
		
		const FString DebugString = FString::Printf(
			TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth
		);
		Debug::Print(DebugString, FColor::Green);
		
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		
		if (GetCurrentHealth() == 0.f)
		{
			UUGRC_FunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), UGRC_GameplayTags::Shared_Status_Death);
		}
	}
}