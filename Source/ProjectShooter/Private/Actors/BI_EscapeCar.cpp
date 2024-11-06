// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BI_EscapeCar.h"
#include <Kismet/GameplayStatics.h>

ABI_EscapeCar::ABI_EscapeCar()
{
}

void ABI_EscapeCar::Interact(ACharacter* Character)
{
    AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(Character);

    if (PlayerCharacter->isPlayerGetDocument==true)
    {
        UGameplayStatics::OpenLevel(this, FName("DocumentsCompleted"));

    }
    else
    {
        UGameplayStatics::OpenLevel(this, FName("DocumentsNonComplete"));
    }
}
