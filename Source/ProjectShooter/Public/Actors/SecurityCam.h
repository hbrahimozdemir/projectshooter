// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecurityCam.generated.h"

class UPawnSensingComponent;
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
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CamMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UShooterPawnSensingComponent* PawnSensingComp;

	APawn* PlayerActor;
	bool bPlayerDetected;
	float DetectionTime;

	UFUNCTION()
	void OnPlayerDetected(APawn* Pawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	void TriggerAlarm();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	



};
