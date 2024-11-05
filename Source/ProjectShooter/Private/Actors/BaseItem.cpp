// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseItem.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Characters/ShooterCharacter.h"
// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ItemRoot;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(ItemRoot);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(ItemMesh);

	// Enable collision and set response to overlap with Pawn
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Enable query only
	InteractionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); // Ignore all
	InteractionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(ItemRoot);
	InteractionWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	// Bind the overlap events
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnOverlapEnd);
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Show the widget
		InteractionWidget->SetVisibility(true);

		// Store reference to this item for interaction
		PlayerCharacter->CurrentInteractableItem = this; // Ensure CurrentInteractableItem is declared in ShooterCharacter
	}
}

void ABaseItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AShooterCharacter* PlayerCharacter = Cast<AShooterCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Hide the widget
		InteractionWidget->SetVisibility(false);

		// Clear the reference to the interactable item
		PlayerCharacter->CurrentInteractableItem = nullptr; // Reset the reference
	}
}
void ABaseItem::Interact(ACharacter* Character)
{
	// Define what happens when the player interacts with the item
	UE_LOG(LogTemp, Warning, TEXT("Interacted with BaseItem!"));
	// Add your interaction logic here (e.g., pick up item, open menu, etc.)
}