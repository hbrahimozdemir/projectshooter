// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SecurityCam.h"
#include "Characters/ShooterCharacter.h"
#include "AISystem/ShooterPawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
ASecurityCam::ASecurityCam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CamMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecurityCamera"));
	RootComponent = CamMesh;

	// ShooterPawnSensingComponent kullanarak algýlama
	PawnSensingComp = CreateDefaultSubobject<UShooterPawnSensingComponent>(TEXT("PawnSensingComp"));
}
void ASecurityCam::BeginPlay()
{
    Super::BeginPlay();

    PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PawnSensingComp)
    {
        PawnSensingComp->OnSeePawn.AddDynamic(this, &ASecurityCam::OnPlayerDetected);
        PawnSensingComp->OnHearNoise.AddDynamic(this, &ASecurityCam::OnNoiseHeard);
    }
}

void ASecurityCam::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bPlayerDetected)
    {
        DetectionTime += DeltaTime;

        if (DetectionTime >= 3.0f)
        {
            UE_LOG(LogTemp, Warning, TEXT("Alarm Triggered! Player detected for 3 seconds."));
            TriggerAlarm();
            bPlayerDetected = false;
        }
    }
    else
    {
        DetectionTime = 0.0f;
    }
}

void ASecurityCam::OnPlayerDetected(APawn* Pawn)
{
    if (Pawn == PlayerActor)
    {
        bPlayerDetected = true;
    }
}

void ASecurityCam::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
    if (NoiseInstigator == PlayerActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Noise heard from player at location: %s"), *Location.ToString());
        // Ýsteðe baðlý olarak alarmý tetikleyebilirsiniz
    }
}

void ASecurityCam::TriggerAlarm()
{
    UE_LOG(LogTemp, Warning, TEXT("Alarm triggered by security camera!"));
}
