// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include <AISystem/ShooterAIController.h>

void AShooterGameMode::KilledEnemy(APawn* Pawn)
{
    APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

    if (PlayerController != nullptr)
    {
        PlayerController->GameHasEnded(nullptr, false);
    }

    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }

    KillAllEnemies(true); // T�m d��manlar �ld�yse kazanma durumu �a�r�l�r.
}


void AShooterGameMode::KillAllEnemies(bool bAllEnemiesKilled)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        // Yaln�zca oyuncu kontrolc�leri i�in GameHasEnded �a�r�s� yap�yoruz
        if (Controller->IsPlayerController())
        {
            bool bIsWinner = bAllEnemiesKilled;
            Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
        }
    }
}

