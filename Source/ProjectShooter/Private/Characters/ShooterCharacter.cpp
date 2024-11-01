// ShooterCharacter.cpp

#include "Characters/ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapon/Weapon.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Spring Arm and Camera Setup
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    CameraBoom->SetupAttachment(GetMesh());
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->TargetArmLength = 210;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

    // Character movement settings
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;

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
}

// Movement functions
void AShooterCharacter::Move(const float AxisValue, const EAxis::Type Axis)
{
    if (Controller && AxisValue != 0.f)
    {
        const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(Axis);
        AddMovementInput(Direction, AxisValue);
    }
}

void AShooterCharacter::MoveForward(float AxisValue)
{
    Move(AxisValue, EAxis::X);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
    Move(AxisValue, EAxis::Y);
}

// Sprint functions
void AShooterCharacter::CharacterStartRunning()
{
    GetCharacterMovement()->MaxWalkSpeed = 700.f;
}

void AShooterCharacter::CharacterStopRunning()
{
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
