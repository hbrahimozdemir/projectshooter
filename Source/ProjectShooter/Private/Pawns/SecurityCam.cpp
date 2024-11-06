#include "Pawns/SecurityCam.h"
#include "Kismet/GameplayStatics.h"
#include "aisystem/ShooterAIController.h" // AI controller'�n�z� burada dahil edin
#include <Perception/PawnSensingComponent.h>
#include <AISystem/ShooterAIController.h>
#include "BehaviorTree/BlackboardComponent.h" 
#include <Components/SpotLightComponent.h>


ASecurityCam::ASecurityCam()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ItemRoot;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(ItemRoot);

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASecurityCam::OnSeePlayer);

	// SpotLight oluşturuyoruz
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(ItemRoot); // Root bileşenine ekliyoruz
	SpotLight->SetVisibility(true);



}

void ASecurityCam::BeginPlay()
{
	Super::BeginPlay();
}

void ASecurityCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASecurityCam::SetCanSeePlayers(bool bCanSee)
{
	bSeePlayer = bCanSee;
}

void ASecurityCam::OnSeePlayer(APawn* SeenPawn)
{
	if (bSeePlayer == false) {
		UE_LOG(LogTemp, Warning, TEXT("ALARM Disabled"));
	}
	
	if (SeenPawn->IsPlayerControlled() && !bAlarmActive && !GetWorldTimerManager().IsTimerActive(AlarmTimer) && bSeePlayer==true)
	{
		// 3 saniye sonra alarm� ba�latmak i�in timer ayarla
		GetWorldTimerManager().SetTimer(AlarmTimer, this, &ASecurityCam::ActivateAlarm, 3.0f, false);
	}
}

void ASecurityCam::ActivateAlarm()
{
    bAlarmActive = true;
    UE_LOG(LogTemp, Warning, TEXT("ALARM!! , ALARM!! Das ist ein Feind "));

    // Alarm sesini çal
    if (AlarmSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, AlarmSound, GetActorLocation());
    }

    // Oyuncunun dünyadaki konumunu al
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    // AI'lara alarm durumunu bildir
    TArray<AActor*> FoundAI;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAIController::StaticClass(), FoundAI);
    for (AActor* AIActor : FoundAI)
    {
        AShooterAIController* AIController = Cast<AShooterAIController>(AIActor);
        if (AIController && AIController->GetBlackboardComponent())
        {
            AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("IsAlarmActive"), true);
            AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
        }
    }

    // Alarmı 5 saniye sonra kapatmak için bir zamanlayıcı ayarla
    GetWorldTimerManager().SetTimer(AlarmTimer, this, &ASecurityCam::DeactivateAlarm, 5.0f, false);
}
void ASecurityCam::DeactivateAlarm()
{
    bAlarmActive = false;
    UE_LOG(LogTemp, Warning, TEXT("Alarm deactivated"));
}
