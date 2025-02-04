// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSHOOTER_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void KilledEnemy(APawn* Pawn);

	void KillAllEnemies(bool bAllEnemiesKilled);

};
