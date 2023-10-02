// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arrow.h"
#include "Arrow_Archer.generated.h"

/**
 * 
 */
UCLASS()
class FLETCHER_API AArrow_Archer : public AArrow
{
	GENERATED_BODY()
	
protected:

	void TargetRotation() override;
};
