// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
//class UNiagaraSystem;
//class UNiagaraComponent;

UCLASS()
class FLETCHER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
		UStaticMeshComponent* StaticMeshComponent;

	float GetDamage() { return Damage; }

	void DestroyProjectile();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnFire();

private:

public:

	//UPROPERTY(EditAnywhere, Category = "Trail")
		//UNiagaraSystem* TrailEffect;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
		float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
		float Damage;

	//UNiagaraComponent* TrailComp;

};
