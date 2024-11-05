// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SecurityCam.generated.h"

UCLASS()
class PROJECTSHOOTER_API ASecurityCam : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASecurityCam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ItemRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* AlarmSound;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCanSeePlayers(bool bCanSee);
	bool bSeePlayer = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpotLightComponent* SpotLight;

private:
	// Oyuncu görüþ alanýna girince çaðrýlacak fonksiyon
	UFUNCTION()
	void OnSeePlayer(APawn* SeenPawn);

	// Alarmý aktif hale getiren fonksiyon
	void ActivateAlarm();

	void DeactivateAlarm();

	// Pawn Sensing Component (oyuncuyu algýlamak için kullanýlýr)
	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComponent;

	// Alarm durumu
	bool bAlarmActive = false;

	bool bCanSeePlayers = true;

	// Alarmý tetiklemek için zamanlayýcý
	FTimerHandle AlarmTimer;
};
