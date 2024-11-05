// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseItem.h"
#include "BI_SecretDocument.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSHOOTER_API ABI_SecretDocument : public ABaseItem
{
	GENERATED_BODY()

public:
	ABI_SecretDocument();

	virtual void Interact(ACharacter* Character);

};
