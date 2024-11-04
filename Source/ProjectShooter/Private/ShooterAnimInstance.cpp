// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "Characters/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include <Kismet/KismetMathLibrary.h>

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
		ShooterCharacter= Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (ShooterCharacter == nullptr) return;
	bIsDead = ShooterCharacter->IsDead();
	FVector Velocity = ShooterCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

	bIsAccelerating = ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	bIsCrouching = ShooterCharacter->GetCharacterMovement()->IsCrouching();

	FRotator AimRotation = ShooterCharacter->GetBaseAimRotation(); // Kameranýn aim rotasyonu
	FRotator MovementRotation = ShooterCharacter->GetActorRotation(); // Karakterin hareket rotasyonu

	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(AimRotation, MovementRotation);
	Yaw = DeltaRot.Yaw;
	Pitch = DeltaRot.Pitch;

	Direction = CalculateDirection(Velocity, ShooterCharacter->GetActorRotation());


}
