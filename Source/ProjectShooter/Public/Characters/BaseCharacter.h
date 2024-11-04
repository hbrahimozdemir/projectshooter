// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Weapon/Weapon.h>
#include "BaseCharacter.generated.h"


UCLASS()
class PROJECTSHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
  ABaseCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
    float CurrentHealth;

    // Silah referansý
    UPROPERTY(EditAnywhere, Category = "Weapon")
    TSubclassOf<AWeapon> WeaponClass;

    UPROPERTY()
    AWeapon* Weapon;

    // Hasar alma ve ölüm durumu fonksiyonlarý
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    UFUNCTION(BlueprintCallable, Category = "Character")
    bool IsDead() const;

    // Ortak Shoot fonksiyonu
    virtual void Shoot();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
