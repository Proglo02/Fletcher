// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "NiagaraFunctionLibrary.h"
//#include "NiagaraComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("SMesh");
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AProjectile::OnFire()
{
	FTimerHandle UnusedHandle;

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AProjectile::DestroyProjectile, LifeTime, false);

	//TrailComp = UNiagaraFunctionLibrary::SpawnSystemAttached(TrailEffect, StaticMeshComponent, FName(""), FVector(0.0f), FRotator(0.0f), EAttachLocation::Type::KeepRelativeOffset, true);
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

