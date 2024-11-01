// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "Characters/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UShooterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}

void UShooterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if (ShooterCharacter == nullptr)
    {
        ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
    }

    if (ShooterCharacter == nullptr) return;

    // Get the character's velocity and remove the Z component
    FVector Velocity = ShooterCharacter->GetVelocity();
    Velocity.Z = 0.f;
    Speed = Velocity.Size();

    // Calculate if the character is in the air
    bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

    // Determine if accelerating
    bIsAccelerating = ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;

    // Check if crouching
    bIsCrouching = ShooterCharacter->GetCharacterMovement()->IsCrouching();

    // Calculate the direction relative to the character’s facing direction
    Direction = CalculateDirection(Velocity, ShooterCharacter->GetActorRotation());
}

