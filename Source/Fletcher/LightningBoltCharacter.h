// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LightningBoltCharacter.generated.h"

class APlayerCharacter;
class ABow;

UCLASS()
class FLETCHER_API ALightningBoltCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALightningBoltCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnDamage(float DamageRatio);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	void FollowPlayer();

	void StartAim();
	void StopAim();

	void Draw();
	void Shoot();

	void Dash();
	void GetDashPoint();
	void StopDashing();

	void StopStagger();

	void OnDeath();

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "LightningBolt")
		float Pitch;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Bow")
		bool Aiming;
		
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Bow")
		bool Drawing;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "LightningBolt")
		bool Dashing;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Bow")
		bool Staggered;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightningBolt")
		float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LightningBolt")
		float CurrentHealth;

protected:

	UPROPERTY(EditAnywhere, Category = "Bow")
		TSubclassOf<AActor> BowSubclass;

	UPROPERTY(EditAnywhere, Category = "LightningBolt")
		float DrawTime;

	UPROPERTY(EditAnywhere, Category = "LightningBolt")
		float ShortDrawTime;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "LightningBolt")
		float CurrentDrawTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LightningBolt")
		float StaggeredTime;

	UPROPERTY(EditInstanceOnly, BLueprintReadonly, Category = "LightningBolt")
		bool IsStaggered;

	UPROPERTY(EditAnywhere, Category = "LightningBolt")
		float DashSpeed;

	AActor* BowActor;
	ABow* BowRef;

private:

	UPROPERTY(EditAnywhere, Category = "Dashing")
		TSubclassOf<AActor> DashPointSubClass;

	APlayerCharacter* PlayerRef;

	TArray<AActor*> DashPoints;

	AActor* CurrentDashPoint;

	FTimerHandle StaggeredHandle;

	bool ShouldDraw;

	int NumDraws;
	int NumHits;
	int NumBetweenDash;
};
