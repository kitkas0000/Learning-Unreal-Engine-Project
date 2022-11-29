#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "MyProject/MyComponents/MyComponent.h"



AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	// CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraBoom->bUsePawnControlRotation = true;

	// Character Configs
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Components
	MyComponent = CreateDefaultSubobject<UMyComponent>(TEXT("MyComponent"));
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Actions
	// Pressed
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMyCharacter::AttackButtonPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::SprintButtonPressed);
	// Released
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::SprintButtonReleased);
	// Axises
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::Turn);
	
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(MyComponent)
	{
		MyComponent->SetCharacter(this);
	}
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	SpeedMode = ESpeedMode::ESM_Jog;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
}

void AMyCharacter::AttackButtonPressed()
{
	MyComponent->RequestAttack();
}

void AMyCharacter::SprintButtonPressed()
{
	SpeedMode = ESpeedMode::ESM_Sprint;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMyCharacter::SprintButtonReleased()
{
	SpeedMode = ESpeedMode::ESM_Jog;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
}

void AMyCharacter::MoveForward(float Value)
{
	// Yaw Pitch Roll
	const FRotator ControllRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControllRotation.Yaw, 0.f);
	const FVector Direction =  FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMyCharacter::MoveRight(float Value)
{
	const FRotator ControllRotation = Controller->GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, ControllRotation.Yaw, 0.f);
	const FVector Direction =  FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMyCharacter::LookUp(float Value)
{
	// Pitch
	AddControllerPitchInput(Value);
}

void AMyCharacter::Turn(float Value)
{
	// Yaw
	AddControllerYawInput(Value);
}
