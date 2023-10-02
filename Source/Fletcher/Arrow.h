// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class FLETCHER_API AArrow : public AProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnShoot(float Charge);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void TargetRotation();

	void RandomRotation( float Charge );

	void SetCurveRotation( FRotator RandomCharge );

public:

protected:

private:

	FRotator CurveRotation;

	bool CanMove;
};
