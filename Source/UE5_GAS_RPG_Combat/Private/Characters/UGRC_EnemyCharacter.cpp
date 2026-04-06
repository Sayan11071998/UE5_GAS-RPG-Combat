#include "Characters/UGRC_EnemyCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/UGRC_EnemyCombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartupData/UGRC_DataAsset_EnemyStartupData.h"
#include "Components/UI/UGRC_EnemyUIComponent.h"
#include "Widgets/UGRC_WidgetBase.h"
#include "UGRC_FunctionLibrary.h"

AUGRC_EnemyCharacter::AUGRC_EnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
	EnemyCombatComponent = CreateDefaultSubobject<UUGRC_EnemyCombatComponent>(TEXT("EnemyCombatComponent"));
	
	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandCollisionBox"));
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AUGRC_EnemyCharacter::OnBodyCollisionBoxBeginOverlap);
	
	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandCollisionBox"));
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AUGRC_EnemyCharacter::OnBodyCollisionBoxBeginOverlap);
	
	EnemyUIComponent = CreateDefaultSubobject<UUGRC_EnemyUIComponent>(TEXT("EnemyUIComponent"));
	
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

TObjectPtr<UUGRC_PawnCombatComponent> AUGRC_EnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

TObjectPtr<UUGRC_PawnUIComponent> AUGRC_EnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

TObjectPtr<UUGRC_EnemyUIComponent> AUGRC_EnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AUGRC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (UUGRC_WidgetBase* HealthWidget = Cast<UUGRC_WidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AUGRC_EnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitEnemyStartupData();
}

#if WITH_EDITOR
void AUGRC_EnemyCharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}
	
	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}
#endif

void AUGRC_EnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UUGRC_FunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void AUGRC_EnemyCharacter::InitEnemyStartupData()
{
	if (CharacterStartupData.IsNull()) return;
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UUGRC_DataAsset_StartupDataBase* LoadedData = CharacterStartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(UGRC_AbilitySystemComponent);
				}
			}
		)
	);
}