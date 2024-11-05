#include "Pawns/SecurityCam.h"
#include "Kismet/GameplayStatics.h"
#include "aisystem/ShooterAIController.h" // AI controller'ýnýzý burada dahil edin
#include <Perception/PawnSensingComponent.h>
#include <AISystem/ShooterAIController.h>
#include "BehaviorTree/BlackboardComponent.h" 

ASecurityCam::ASecurityCam()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASecurityCam::OnSeePlayer);
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
	bCanSeePlayers = bCanSee;
}

void ASecurityCam::OnSeePlayer(APawn* SeenPawn)
{
	if (!bCanSeePlayers) UE_LOG(LogTemp, Warning, TEXT("ALARM DISABLED ")); return;
	if (SeenPawn->IsPlayerControlled() && !bAlarmActive && !GetWorldTimerManager().IsTimerActive(AlarmTimer))
	{
		// 3 saniye sonra alarmý baþlatmak için timer ayarla
		GetWorldTimerManager().SetTimer(AlarmTimer, this, &ASecurityCam::ActivateAlarm, 3.0f, false);
	}
}

void ASecurityCam::ActivateAlarm()
{
	bAlarmActive = true;
	UE_LOG(LogTemp, Warning, TEXT("ALARM!! , ALARM!! Das ist ein Feind "));
	// Oyuncunun dünyadaki konumunu al
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;  // Eðer oyuncu bulunamazsa fonksiyondan çýk
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
}
