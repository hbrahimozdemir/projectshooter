// Fill out your copyright notice in the Description page of Project Settings.


#include "AISystem/ShooterPawnSensingComponent.h"

UShooterPawnSensingComponent::UShooterPawnSensingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // Varsayılan ayarlar
   
}

void UShooterPawnSensingComponent::BeginPlay()
{
    Super::BeginPlay();

    // Sensing ayarlarını güncelle
    
}

