// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecurityCam.generated.h"

UCLASS()
class PROJECTSHOOTER_API ASecurityCam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASecurityCam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Check for player in line of sight
	void CheckVisualDetection();

	// Detection variables
	UPROPERTY(EditAnywhere)
	float DetectionRange = 1000.0f; // Maximum range to detect player

	UPROPERTY(EditAnywhere)
	float AlarmThreshold = 3.0f; // Time required to trigger the alarm

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CamMesh;
	// Player reference
	AActor* PlayerActor;
	// Variables to track detection
	bool bIsPlayerVisible = false;
	float DetectionTime = 0.0f;

	// Function to trigger alarm
	void TriggerAlarm();
};
