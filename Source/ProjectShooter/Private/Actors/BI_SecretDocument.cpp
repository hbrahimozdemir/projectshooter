// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BI_SecretDocument.h"

ABI_SecretDocument::ABI_SecretDocument()
{
	

}

void ABI_SecretDocument::Interact(ACharacter* Character)
{
    // Karakteri ShooterCharacter olarak cast et ve isPlayerGetDocument deðerini true yap
    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(Character);
    if (ShooterCharacter)
    {
        ShooterCharacter->isPlayerGetDocument = true;
    }

    // Belgeyi yok et
    ItemMesh->DestroyComponent();
    InteractionBox->DestroyComponent();
}