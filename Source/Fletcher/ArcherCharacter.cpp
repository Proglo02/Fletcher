// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"
#include "PlayerCharacter.h"
#include "Bow.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AArcherCharacter::AArcherCharacter()
: DrawTime( 5.0f )
, DetectionRange( 5000.0f )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArcherCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	BowActor = GetWorld()->SpawnActor<AActor>(BowSubclass);
	BowActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "BowSocket");

	BowRef = Cast<ABow>(BowActor);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AArcherCharacter::OnHit);
}

void AArcherCharacter::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

bool AArcherCharacter::CheckPlayerVisible()
{
	if (PlayerRef)
	{
		FVector ArcherToPlayer = GetActorLocation() - PlayerRef->GetActorLocation();

		float DistanceToPlayer = ArcherToPlayer.Length();

		if (DistanceToPlayer < DetectionRange)
		{
			float DotProduct = FVector::DotProduct(GetActorForwardVector(), ArcherToPlayer);

			if (DotProduct < -30.0f)
			{
				FHitResult HitResult;

				GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), PlayerRef->GetActorLocation(), ECollisionChannel::ECC_Visibility);

				if (!HitResult.GetActor())
				{
					return true;
				}
			}
		}
	}

	return false;
}

void AArcherCharacter::StartAim()
{
	Aiming = true;
}

void AArcherCharacter::StopAim()
{
	Aiming = false;

	BowRef->StopDraw();
	Drawing = false;
}

void AArcherCharacter::Draw()
{
	if (Aiming)
	{
		BowRef->StartDraw();
		Drawing = true;

		FTimerHandle UnusedHandle;

		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AArcherCharacter::Shoot, DrawTime, false);
	}
}

void AArcherCharacter::Shoot()
{
	if (Aiming)
	{
		BowRef->Shoot();

		Drawing = false;
	}
}

// Called every frame
void AArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckPlayerVisible())
	{

		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerRef->GetActorLocation()));

		Pitch = GetActorRotation().Pitch;

		SetActorRotation(FRotator(0.0f, GetActorRotation().Yaw, 0.0f));

		StartAim();

		if (!Drawing && BowRef->Reloaded)
		{
			Draw();
		}
	}
	else
	{
		StopAim();
	}
}

// Called to bind functionality to input
void AArcherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

