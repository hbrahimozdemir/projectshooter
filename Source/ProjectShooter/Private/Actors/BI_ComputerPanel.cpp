// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BI_ComputerPanel.h"
#include <Pawns/SecurityCam.h>
#include <Kismet/GameplayStatics.h>


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
   
    InteractionWidget->SetVisibility(false);
    // Oyuncu etkile�ime girdi�inde, g�venlik kameralar�n� devre d��� b�rak
    TArray<AActor*> FoundCams;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASecurityCam::StaticClass(), FoundCams);
    for (AActor* CamActor : FoundCams)
    {
        ASecurityCam* SecurityCam = Cast<ASecurityCam>(CamActor);
        if (SecurityCam)
        {
            SecurityCam->SetCanSeePlayers(false);
        }
    }
}