// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "Arrow.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABow::ABow()
	: ChargeSpeed(2.5f)
	, ReloadSpeed(0.7f)
	, Reloaded(true)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	Arrow = nullptr;
}

// Called when the game starts or when spawned
void ABow::BeginPlay()
{
	Super::BeginPlay();

	Reload();
}

void ABow::StartDraw()
{
	if (Arrow)
		Drawing = true;
}

void ABow::StopDraw()
{
	Drawing = false;
	Charge = 0.0f;
}

void ABow::Shoot()
{
	if (Arrow)
	{
		Drawing = false;

		HasShot = true;

		Reloaded = false;

		Arrow->OnShoot(Charge);

		Arrow = nullptr;

		Charge = 0.0f;

		FTimerHandle UnusedHandle;

		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABow::Reload, ReloadSpeed, false);
	}
}

void ABow::SpawnArrow()
{
	Arrow = Cast<AArrow>(GetWorld()->SpawnActor<AActor>(ArrowSubclass, SkeletalMeshComponent->GetBoneLocation("String52"), GetActorRotation()));
}

void ABow::Reload()
{
	HasShot = false;

	Reloaded = true;

	SpawnArrow();

	Arrow->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform, "String52");
}

void ABow::OnDestroy()
{
	if (Arrow)
		Arrow->DestroyProjectile();
}

// Called every frame
void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Drawing)
	{
		Charge += DeltaTime * ChargeSpeed;

		Charge = FMath::Clamp(Charge, 0.0f, 1.0f);
	}
}

