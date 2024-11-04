// BaseCharacter.cpp

#include "Characters/BaseCharacter.h"
#include "Components/CapsuleComponent.h"

ABaseCharacter::ABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    CurrentHealth = MaxHealth;
}

void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;

    // Silahý karaktere atama
    if (WeaponClass)
    {
        Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
        if (Weapon)
        {
            Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
            Weapon->SetOwner(this);
        }
    }
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = FMath::Min(CurrentHealth, DamageAmount);
    CurrentHealth -= DamageToApply;

    if (IsDead())
    {
        DetachFromControllerPendingDestroy();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    return DamageToApply;
}

bool ABaseCharacter::IsDead() const
{
    return CurrentHealth <= 0;
}

void ABaseCharacter::Shoot()
{
    if (Weapon)
    {
        Weapon->PullTrigger();
    }
}
