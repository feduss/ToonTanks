// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Get the world timer manager and set a new timer
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle, //Unique timer (handle) that can be used to distinguish timers that have identical delegates.
		this, //class in which call the function timer?
		&ATower::CheckFireCondition, //function to call when the timer is gone
		FireRate, //the function is called every "fire rate" seconds
		true //in loop
	);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank != nullptr && InFireRange()) {
		//If yes, rotate the turret
		RotateCannon(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition() {

	if (InFireRange()) {
		InstantiateProjectile();
	}
}

bool ATower::InFireRange() {
	if (Tank != nullptr) {
		//Find the distance to the tank
		FVector TowerLoc = GetActorLocation();
		FVector TankLoc = Tank->GetActorLocation();
		Distance = FVector::Dist(TowerLoc, TankLoc);

		//Check if tank is in range
		if (Distance <= FireRange) {
			return true;
		}
	}

	return false;
}