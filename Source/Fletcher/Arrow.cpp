// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
//#include "NiagaraFunctionLibrary.h"
//#include "NiagaraComponent.h"

// Sets default values
AArrow::AArrow()
: CanMove( false )
, CurveRotation( 0.0f, 0.0f, 0.0f )
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AArrow::OnShoot(float Charge)
{
	OnFire();

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnOverlapBegin);

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	TargetRotation();
	RandomRotation( Charge );

	Charge = FMath::Clamp(Charge, 0.2f, 1.0f);

	ProjectileMovementComponent->Velocity = GetActorRotation().Vector() * Speed;

	CanMove = true;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanMove)
	{
		AddActorWorldRotation(CurveRotation);

		if (ProjectileMovementComponent)
			ProjectileMovementComponent->Velocity = GetActorRotation().Vector() * Speed;

		StaticMeshComponent->SetWorldRotation(ProjectileMovementComponent->Velocity.Rotation());
	}
}

void AArrow::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ProjectileMovementComponent)
		ProjectileMovementComponent->DestroyComponent();

	if (OtherActor)
		AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);

	//if (TrailComp)
		//TrailComp->DestroyComponent();

	StaticMeshComponent->SetGenerateOverlapEvents(false);

	CanMove = false;
}

void AArrow::TargetRotation()
{

}

void AArrow::RandomRotation( float Charge )
{
	float ReverseCharge = 1.0f - Charge;

	FRotator RandomRotation = FRotator(FMath::RandRange(-ReverseCharge, ReverseCharge) * 5, FMath::RandRange(-ReverseCharge, ReverseCharge) * 5, FMath::RandRange(-ReverseCharge, ReverseCharge) * 5);

	AddActorWorldRotation(RandomRotation);

	SetCurveRotation(RandomRotation);
}

void AArrow::SetCurveRotation(FRotator RandomRotation)
{

	CurveRotation = FRotator(RandomRotation.Pitch * 0.1f, FMath::Abs(RandomRotation.Roll * 0.05f), 0.0f);
}
