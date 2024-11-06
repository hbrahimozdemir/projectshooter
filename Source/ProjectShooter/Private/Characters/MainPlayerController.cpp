// Fill out your copyright notice in the Description page of Project Settings
#include "Characters/MainPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    CrossHair = CreateWidget(this, CrossHairWidget);
    if (CrossHair != nullptr) {
        CrossHair->AddToViewport();
    } 
    HealthBar = CreateWidget(this, HealthBarWidget);
    if (HealthBar != nullptr) {
        HealthBar->AddToViewport();
    }
}

void AMainPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    if (bIsWinner)
    {
        UUserWidget* CarSubtitle = CreateWidget(this, CarSubWidget);
        if (CarSubtitle != nullptr) {
            CarSubtitle->AddToViewport();
        }
    }
    else
    {
        UUserWidget* DeadScreen = CreateWidget(this, DeadScreenClass);
        if (DeadScreen != nullptr) {
            CrossHair->RemoveFromViewport();
            HealthBar->RemoveFromViewport();
            DeadScreen->AddToViewport();
            bShowMouseCursor = true;
            SetInputMode(FInputModeUIOnly());
        }
    }

    Super::GameHasEnded(EndGameFocus, bIsWinner);
}

void AMainPlayerController::RestartLevelInBlueprint()
{
    bShowMouseCursor = false;
    SetInputMode(FInputModeGameOnly()); // Sadece oyun girdi moduna geç

    // Seviye yeniden baþlatma
    RestartLevel();
  
}