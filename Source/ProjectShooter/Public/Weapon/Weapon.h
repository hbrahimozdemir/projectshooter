// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROJECTSHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	void PullTrigger();

	virtual void Tick(float DeltaTime) override;
protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category="Weapon Properties")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category= "Weapon Properties")
	class USceneComponent* WeaponRoot;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	float BulletRange=1000;
};
