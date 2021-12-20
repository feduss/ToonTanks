// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"


void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();

	HandleGameStart();

	NumberOfTowers = GetNumberOfTowers();
}

void AToonTanksGameMode::HandleGameStart() {
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (ToonTanksPlayerController != nullptr) {
		StartGame();
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnabledTimerHandle;

		//FTimerDelegate is useful to call a function that requires params when a timer expires
		FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);

		//After StartDelay(seconds), call SetPlayerEnabledState in ToonTanksPlayerController
		GetWorldTimerManager().SetTimer(
			PlayerEnabledTimerHandle,
			InputDelegate,
			StartDelay,
			false //not looping
			);
	}
}


void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
	//If the dead actor is the tank, call its handle destruction function
	//disable input and the mouse cursor
	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		if (ToonTanksPlayerController != nullptr) {
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else {
		ATower* Tower = Cast<ATower>(DeadActor);

		if (Tower != nullptr) {
			Tower->HandleDestruction();
		}

		NumberOfTowers--;

		if (NumberOfTowers == 0) {
			GameOver(true);
		}
	}
}

int32 AToonTanksGameMode::GetNumberOfTowers() {
	TArray<ATower*> Towers = TArray<ATower*>();
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}