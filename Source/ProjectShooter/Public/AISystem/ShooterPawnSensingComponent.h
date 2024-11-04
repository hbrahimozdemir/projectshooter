// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/PawnSensingComponent.h"
#include "ShooterPawnSensingComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSHOOTER_API UShooterPawnSensingComponent : public UPawnSensingComponent
{
	GENERATED_BODY()
public:
	UShooterPawnSensingComponent();

protected:
	// Görüþ ve ses algýlama olaylarýný burada tanýmlayýn
	virtual void BeginPlay() override;

public:
	

};
