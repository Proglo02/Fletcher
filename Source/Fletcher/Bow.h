// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bow.generated.h"

class USkeletalMeshComponent;
class AArrow;

UCLASS()
class FLETCHER_API ABow : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ABow();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void StartDraw();
	void StopDraw();

	void Shoot();

	void SpawnArrow();

	void Reload();

	UFUNCTION()
	void OnDestroy();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bow")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bow")
	float Charge;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bow")
	float ChargeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bow")
	float ReloadSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bow")
	bool Drawing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bow")
	bool HasShot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bow")
	bool Reloaded;

private:

	UPROPERTY(EditAnywhere, Category = "Arrow")
	TSubclassOf<AActor> ArrowSubclass;

	AArrow* Arrow;
};
