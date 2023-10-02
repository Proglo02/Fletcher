// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_Archer.h"
#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

void AArrow_Archer::TargetRotation()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation() + FVector(0.0f, 0.0f, 50.0f)));
}
