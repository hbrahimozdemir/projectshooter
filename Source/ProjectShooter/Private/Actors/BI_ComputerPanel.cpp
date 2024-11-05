// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BI_ComputerPanel.h"

ABI_ComputerPanel::ABI_ComputerPanel()
{
    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PointLight->SetupAttachment(ItemMesh); // Attach to the root component
    PointLight->SetLightColor(FColor::Green); // Set initial color to green
    PointLight->SetVisibility(true);
}

void ABI_ComputerPanel::Interact(ACharacter* Character)
{
    // Change the light color to red when the player interacts
    PointLight->SetLightColor(FColor::Red);
}