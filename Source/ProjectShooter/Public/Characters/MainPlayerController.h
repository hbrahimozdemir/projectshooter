// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSHOOTER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
void RestartLevelInBlueprint();
private:
	FTimerHandle TimerHandle;
	float DelayTime = 5.0f; // Gecikme süresi

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> DeadScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CarSubWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CrossHairWidget;





};
