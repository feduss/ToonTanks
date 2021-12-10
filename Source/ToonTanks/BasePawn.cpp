// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a new capsule component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	//Assign this new capsule component as root component
	RootComponent = CapsuleComponent;

	//Create two mesh component
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	Cannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));

	//Attach the body mesh to capsule component and the cannon to the body
	Body->SetupAttachment(CapsuleComponent);
	Cannon->SetupAttachment(Body);

	//Create the projectile spawn point...we need only the base component, so a scene component
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile spawn point");
	//And attach it to the cannon
	ProjectileSpawnPoint->SetupAttachment(Cannon);
}

void ABasePawn::RotateCannon(FVector Value) {
	FVector TargetLocation = Value - Cannon->GetComponentLocation();
	FRotator TargetRotation = FRotator(0.f, TargetLocation.Rotation().Yaw, 0.f);
	Cannon->SetWorldRotation(TargetRotation);
}

void ABasePawn::InstantiateProjectile() {
	DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnPoint->GetComponentLocation(),
		30.f,
		12,
		FColor::Red,
		false,
		3.0f
	);
}

