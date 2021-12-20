// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

protected:

	void BeginPlay() override;

	//Blueprint implementable event is a event that you implement in blueprint but you can call in c++
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bGameWon); //if true, handle display VX of victory

private:
	void HandleGameStart();

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;

	float StartDelay = 3.f;

	int32 NumberOfTowers = 0;
	int32 GetNumberOfTowers();

};
