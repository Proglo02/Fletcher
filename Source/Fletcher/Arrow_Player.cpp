

// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Player.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

void AArrow_Player::TargetRotation()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UCameraComponent* Camera = Player->Camera;

	FHitResult Hit;

	FVector Location;
	FRotator Rotation;

	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(Location, Rotation);

	FVector TraceStart = Camera->GetComponentLocation();

	FVector TraceEnd = TraceStart + Rotation.Vector() * 10000;

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (Hit.GetActor())
	{
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.Location));
	}
	else
	{
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TraceEnd));
	}
}
