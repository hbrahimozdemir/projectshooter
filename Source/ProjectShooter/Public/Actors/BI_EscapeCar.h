// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseItem.h"
#include "BI_EscapeCar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSHOOTER_API ABI_EscapeCar : public ABaseItem
{
	GENERATED_BODY()

public:
	ABI_EscapeCar();

	virtual void Interact(ACharacter* Character);
};
