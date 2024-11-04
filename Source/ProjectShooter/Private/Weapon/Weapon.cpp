// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(WeaponRoot);
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AWeapon::PullTrigger()
{
    UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, WeaponMesh, TEXT("Muzzle"));

    // Play the firing sound
    if (FireSound)  // Check if the sound asset is set
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }

    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn == nullptr) return;
    AController* OwnerController = OwnerPawn->GetController();
    if (OwnerController == nullptr) return;

    FVector Location;
    FRotator Rotation;
    OwnerController->GetPlayerViewPoint(Location, Rotation);

    FVector TraceEnd = Location + Rotation.Vector() * BulletRange;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());
    bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);

    if (bSuccess)
    {
        FVector ShotDirection = -Rotation.Vector();

        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

        AActor* HitActor = Hit.GetActor();
        if (HitActor != nullptr)
        {
            FPointDamageEvent DamageEvent(WeaponDamage, Hit, ShotDirection, nullptr);
            HitActor->TakeDamage(WeaponDamage, DamageEvent, OwnerController, this);
        }
    }
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

