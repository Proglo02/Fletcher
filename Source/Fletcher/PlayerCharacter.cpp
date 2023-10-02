// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
: Aiming( false )
, BaseTurnRate(45.0f)
, BaseLookUpRate(45.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Bow = GetWorld()->SpawnActor<AActor>(BowSubclass, Camera->GetComponentTransform());
	Bow->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "LeftHand");
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRun);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &APlayerCharacter::StartAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &APlayerCharacter::StopAim);

	PlayerInputComponent->BindAction("Draw/Release", IE_Pressed, this, &APlayerCharacter::Draw);
	PlayerInputComponent->BindAction("Draw/Release", IE_Released, this, &APlayerCharacter::Shoot);

	PlayerInputComponent->BindAxis("Forward/Backward", this, &APlayerCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis("Left/Right", this, &APlayerCharacter::MoveLeftRight);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}

void APlayerCharacter::MoveForwardBackward(float value)
{
	if (Controller && value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void APlayerCharacter::MoveLeftRight(float value)
{
	if (Controller && value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void APlayerCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 1500.0f;
}

void APlayerCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void APlayerCharacter::StartJump()
{
	ACharacter::Jump();
}

void APlayerCharacter::StopJump()
{
	ACharacter::StopJumping();
}

void APlayerCharacter::StartAim()
{
	Aiming = true;
}

void APlayerCharacter::StopAim()
{
	Aiming = false;
}

void APlayerCharacter::Draw()
{
}

void APlayerCharacter::Shoot()
{
}


