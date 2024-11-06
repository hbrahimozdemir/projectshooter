// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseItem.h"
#include "BI_ComputerPanel.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSHOOTER_API ABI_ComputerPanel : public ABaseItem
{
	GENERATED_BODY()

public:
	ABI_ComputerPanel();

	UPROPERTY(VisibleAnywhere,Category="Lights")
	class UPointLightComponent* PointLight;

	virtual void Interact(ACharacter* Character);

};
