// ShooterCharacter.cpp

#include "Characters/ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapon/Weapon.h"
#include "Actors/BaseItem.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Spring Arm and Camera Setup
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    CameraBoom->SetupAttachment(GetMesh());
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->TargetArmLength = 300;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

    //// Character movement settings
    //bUseControllerRotationYaw = false;
    //GetCharacterMovement()->bOrientRotationToMovement = true;
    CurrentHealth = MaxHealth;
    // Enable crouch capability
    if (GetMovementComponent())
    {
        GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
    }
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;

    Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
    Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
    Weapon->SetOwner(this);

    

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

    // Bind sprint actions
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AShooterCharacter::CharacterStartRunning);
    PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AShooterCharacter::CharacterStopRunning);

    // Bind crouch toggle action
    PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ToggleCrouch);
    //bind 
    PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);

    PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Interact);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
    CurrentHealth -= DamageToApply;
    UE_LOG(LogTemp, Warning, TEXT("Health Left %f"), CurrentHealth);
    if (IsDead())
    {
        DetachFromControllerPendingDestroy();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
    return CurrentHealth <= 0;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
    AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector() * AxisValue);
}


// Sprint functions
void AShooterCharacter::CharacterStartRunning()
{
    // Karakterin ileri yönde hareket edip etmediðini kontrol et
    float ForwardAxisValue = GetInputAxisValue(TEXT("MoveForward"));

    // Yalnýzca ileri giderken koþmayý etkinleþtir
    if (ForwardAxisValue > 0)
    {
        GetCharacterMovement()->MaxWalkSpeed = 700.f;
    }
}

void AShooterCharacter::CharacterStopRunning()
{
    // Koþmayý durdur ve normal hýza dön
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

// Toggle crouch function
void AShooterCharacter::ToggleCrouch()
{
    if (bIsCrouched)
    {
        UnCrouch();
    }
    else
    {
        Crouch();
       
    }
}

void AShooterCharacter::Shoot()
{
    Weapon->PullTrigger();

}
void AShooterCharacter::Interact()
{
    if (CurrentInteractableItem)
    {
        CurrentInteractableItem->Interact(this); // Call Interact on the current item
    }
}
