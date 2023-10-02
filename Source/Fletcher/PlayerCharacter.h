// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class FLETCHER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void MoveForwardBackward(float value);
	void MoveLeftRight(float value);

	void StartRun();
	void StopRun();

	void StartJump();
	void StopJump();

	void StartAim();
	void StopAim();

	void Draw();
	void Shoot();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* Camera;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Bow")
		bool Aiming;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Bow")
		TSubclassOf<AActor> BowSubclass;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float BaseTurnRate;

	UPROPERTY(EditAnywhere, Category = "Camera")
		float BaseLookUpRate;

	AActor* Bow;

};
