// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AWeapon;

UCLASS()
class PROJECTSHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

private:
	void Move(const float AxisValue, const EAxis::Type Axis);

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void CharacterStartRunning();

	void CharacterStopRunning();

	void ToggleCrouch();


	//

	UPROPERTY(VisibleAnywhere,Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* FollowCamera; 

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;


	UPROPERTY()
	AWeapon* Weapon;

};
