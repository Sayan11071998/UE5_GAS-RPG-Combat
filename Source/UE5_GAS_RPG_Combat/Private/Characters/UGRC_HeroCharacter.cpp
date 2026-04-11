#include "Characters/UGRC_HeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/UGRC_DataAsset_InputConfig.h"
#include "Components/Input/UGRC_InputComponent.h"
#include "UGRC_GameplayTags.h"
#include "AbilitySystem/UGRC_AbilitySystemComponent.h"
#include "DataAssets/StartupData/UGRC_DataAsset_HeroStartupData.h"
#include "Components/Combat/UGRC_HeroCombatComponent.h"
#include "Components/UI/UGRC_HeroUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

AUGRC_HeroCharacter::AUGRC_HeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	HeroCombatComponent = CreateDefaultSubobject<UUGRC_HeroCombatComponent>(TEXT("HeroCombatComponent"));
	HeroUIComponent = CreateDefaultSubobject<UUGRC_HeroUIComponent>(TEXT("HeroUIComponent"));
}

TObjectPtr<UUGRC_PawnCombatComponent> AUGRC_HeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

TObjectPtr<UUGRC_PawnUIComponent> AUGRC_HeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

TObjectPtr<UUGRC_HeroUIComponent> AUGRC_HeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AUGRC_HeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!CharacterStartupData.IsNull())
	{
		if (UUGRC_DataAsset_StartupDataBase* LoadedData = CharacterStartupData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(UGRC_AbilitySystemComponent);
		}
	}
}

void AUGRC_HeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));
	
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	
	UUGRC_InputComponent* UGRCInputComponent = CastChecked<UUGRC_InputComponent>(PlayerInputComponent);
	
	UGRCInputComponent->BindNativeInputAction(InputConfigDataAsset, UGRC_GameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &AUGRC_HeroCharacter::Input_Move);
	UGRCInputComponent->BindNativeInputAction(InputConfigDataAsset, UGRC_GameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AUGRC_HeroCharacter::Input_Look);
	
	UGRCInputComponent->BindNativeInputAction(InputConfigDataAsset, UGRC_GameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &AUGRC_HeroCharacter::Input_SwitchTargetTriggered);
	UGRCInputComponent->BindNativeInputAction(InputConfigDataAsset, UGRC_GameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &AUGRC_HeroCharacter::Input_SwitchTargetCompleted);
	UGRCInputComponent->BindNativeInputAction(InputConfigDataAsset, UGRC_GameplayTags::InputTag_PickUp_Stones, ETriggerEvent::Started, this, &AUGRC_HeroCharacter::Input_PickUpStonesStarted);

	UGRCInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AUGRC_HeroCharacter::Input_AbilityInputPressed, &AUGRC_HeroCharacter::Input_AbilityInputReleased);
}

void AUGRC_HeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AUGRC_HeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AUGRC_HeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVectorVector = InputActionValue.Get<FVector2D>();
	
	if (LookAxisVectorVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVectorVector.X);
	}
	
	if (LookAxisVectorVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVectorVector.Y);
	}
}

void AUGRC_HeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AUGRC_HeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? UGRC_GameplayTags::Player_Event_SwitchTarget_Right : UGRC_GameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
}

void AUGRC_HeroCharacter::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		UGRC_GameplayTags::Player_Event_ConsumeStones,
		Data
	);
}

void AUGRC_HeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	UGRC_AbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AUGRC_HeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	UGRC_AbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}