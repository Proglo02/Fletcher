// Fill out your copyright notice in the Description page of Project Settings.


#include "LightningBoltCharacter.h"
#include "PlayerCharacter.h"
#include "Bow.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ALightningBoltCharacter::ALightningBoltCharacter()
: CurrentDashPoint( nullptr )
, Dashing( false )
, NumDraws( 0 )
, NumBetweenDash( 3 )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightningBoltCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	BowActor = GetWorld()->SpawnActor<AActor>(BowSubclass);
	BowActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "BowSocket");

	BowRef = Cast<ABow>(BowActor);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ALightningBoltCharacter::OnHit);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), DashPointSubClass, DashPoints);

	CurrentHealth = MaxHealth;
}

// Called every frame
void ALightningBoltCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FollowPlayer();

	if (!Drawing && BowRef->Reloaded && NumDraws < NumBetweenDash && !Staggered)
	{
		Draw();
	}
	else if (NumDraws >= NumBetweenDash && !Dashing && !Drawing && BowRef->Reloaded && !Staggered)
	{
		Dash();
	}

	if (!Dashing && !Aiming && !Staggered)
	{
		StartAim();
	}

	if (Dashing)
	{
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CurrentDashPoint->GetActorLocation(), DeltaTime, DashSpeed));

		FVector DashLocation = CurrentDashPoint->GetActorLocation();

		if ((GetActorLocation() - DashLocation).Length() < 10.0f)
		{
			StopDashing();

			NumDraws = 0;
		}
	}
}

void ALightningBoltCharacter::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Staggered)
	{
		Staggered = true;
		StopAim();

		GetWorldTimerManager().SetTimer(StaggeredHandle, this, &ALightningBoltCharacter::StopStagger, StaggeredTime, false);

		return;
	}

	AProjectile* ProjectileRef = Cast<AProjectile>(OtherActor);

	if (ProjectileRef)
	{
		float Damage = ProjectileRef->GetDamage();

		float DamageRatio = Damage / MaxHealth;

		CurrentHealth -= Damage;

		OnDamage(DamageRatio);

		if (CurrentHealth <= MaxHealth * 0.5f)
		{
			NumBetweenDash = 1;
			DrawTime = 1.0f;
		}

		NumHits++;

		if (NumHits >= 3)
		{
			StopStagger();

			GetWorldTimerManager().ClearTimer(StaggeredHandle);
		}

		if (CurrentHealth <= 0.0f)
		{
			OnDeath();
		}
	}
}

void ALightningBoltCharacter::FollowPlayer()
{
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerRef->GetActorLocation()));

	Pitch = GetActorRotation().Pitch;

	SetActorRotation(FRotator(0.0f, GetActorRotation().Yaw, 0.0f));
}

void ALightningBoltCharacter::StartAim()
{
	Aiming = true;

	ShouldDraw = true;
}

void ALightningBoltCharacter::StopAim()
{
	Aiming = false;

	BowRef->StopDraw();
	Drawing = false;
}

void ALightningBoltCharacter::Draw()
{
	if (Aiming)
	{
		BowRef->StartDraw();
		Drawing = true;

		NumDraws++;

		CurrentDrawTime = DrawTime;

		if (NumDraws > 1)
			CurrentDrawTime = ShortDrawTime;

		FTimerHandle UnusedHandle;

		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ALightningBoltCharacter::Shoot, CurrentDrawTime, false);
	}
}

void ALightningBoltCharacter::Shoot()
{
	if (Aiming)
	{
		BowRef->Shoot();
		
		Drawing = false;
	}
}

void ALightningBoltCharacter::Dash()
{
	Dashing = true;

	GetDashPoint();

	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
}

void ALightningBoltCharacter::GetDashPoint()
{
	AActor* PrevDashPoint = CurrentDashPoint;

	CurrentDashPoint = DashPoints[FMath::RandRange(0, DashPoints.Num() - 1)];

	if (PrevDashPoint == CurrentDashPoint)
		GetDashPoint();
}

void ALightningBoltCharacter::StopDashing()
{
	Dashing = false;

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
}

void ALightningBoltCharacter::StopStagger()
{
	Staggered = false;
	NumHits = 0;

	Dash();
}

void ALightningBoltCharacter::OnDeath()
{
	BowRef->OnDestroy();

	TArray<AActor*> AttachedActors;

	GetAttachedActors(AttachedActors);

	for (AActor* AttatchedActor : AttachedActors)
	{
		AttatchedActor->Destroy();
	}

	Destroy();
}

// Called to bind functionality to input
void ALightningBoltCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

