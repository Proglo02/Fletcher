// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_LightningBolt.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void AArrow_LightningBolt::TargetRotation()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	FVector Velocity = Player->GetMovementComponent()->Velocity;

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f) - Velocity));
}