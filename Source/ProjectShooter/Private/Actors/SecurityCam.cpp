// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SecurityCam.h"
#include "Characters/ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
ASecurityCam::ASecurityCam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CamMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecurityCamera"));
	RootComponent = CamMesh;
}

void ASecurityCam::BeginPlay()
{
	Super::BeginPlay();
	// Reference to player
	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void ASecurityCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if player is in line of sight
	CheckVisualDetection();

	// If player is visible, increase detection time
	if (bIsPlayerVisible)
	{
		DetectionTime += DeltaTime;

		// Trigger the alarm if the detection time exceeds the threshold
		if (DetectionTime >= AlarmThreshold)
		{
			TriggerAlarm();
		}
	}
	else
	{
		// Reset detection time if player is not visible
		DetectionTime = 0.0f;
	}
}

// Check if player is within line of sight
void ASecurityCam::CheckVisualDetection()
{
	if (!PlayerActor) return;

	// Perform a line trace from the camera to the player
	FHitResult HitResult;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = PlayerActor->GetActorLocation();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignore the camera itself

	// Perform the line trace
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);

	// Set bIsPlayerVisible based on whether the line trace hit the player
	bIsPlayerVisible = bHit && HitResult.GetActor() == PlayerActor;
}

void ASecurityCam::TriggerAlarm()
{
	// Log a message to the output log for testing
	UE_LOG(LogTemp, Warning, TEXT("Alarm Triggered by Security Camera!"));

	// Reset the detection time after triggering the alarm
	DetectionTime = 0.0f;
}

