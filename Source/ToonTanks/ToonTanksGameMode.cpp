// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
	//If the dead actor is the tank, call its handle destruction function
	//disable input and the mouse cursor
	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		if (ToonTanksPlayerController != nullptr) {
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
	}
	else {
		ATower* Tower = Cast<ATower>(DeadActor);

		if (Tower != nullptr) {
			Tower->HandleDestruction();
		}
	}
}

void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

}