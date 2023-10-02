// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArcherCharacter.generated.h"

class APlayerCharacter;
class ABow;

UCLASS()
class FLETCHER_API AArcherCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArcherCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	bool CheckPlayerVisible();

	void StartAim();
	void StopAim();

	void Draw();
	void Shoot();

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Archer")
		float Pitch;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Bow")
		bool Aiming;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Bow")
		bool Drawing;

protected:

	UPROPERTY(EditAnywhere, Category = "Bow")
		TSubclassOf<AActor> BowSubclass;

	UPROPERTY(EditAnywhere, Category = "Archer")
		float DetectionRange;

	UPROPERTY(EditAnywhere, Category = "Archer")
		float DrawTime;

	AActor* BowActor;
	ABow* BowRef;

private:

	APlayerCharacter* PlayerRef;
	
};
