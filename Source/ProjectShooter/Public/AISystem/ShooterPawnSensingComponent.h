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
	// G�r�� ve ses alg�lama olaylar�n� burada tan�mlay�n
	virtual void BeginPlay() override;

public:
	

};
