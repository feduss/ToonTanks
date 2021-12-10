// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank != nullptr) {
		//Find the distance to the tank
		FVector TowerLoc = GetActorLocation();
		FVector TankLoc = Tank->GetActorLocation();
		float Distance = FVector::Dist(TowerLoc, TankLoc);

		//Check if tank is in range
		if (Distance < FireRange) {
			//If yes, rotate the turret
			RotateCannon(TankLoc);
		}
	}
}