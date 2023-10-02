// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arrow.h"
#include "Arrow_Player.generated.h"

/**
 * 
 */
UCLASS()
class FLETCHER_API AArrow_Player : public AArrow
{
	GENERATED_BODY()
	
protected:

	void TargetRotation() override;
};
