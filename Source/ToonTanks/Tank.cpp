// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() {
	//Create a USpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

	//Create a UCameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

	//Attach CameraComponent to SpringArmComponent as child
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind axis "MoveForward" to function Move
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

}

void ATank::Move(float Value) {
	//UE_LOG(LogTemp, Warning, TEXT("Move: %f"), Value);
	FVector DeltaLocation = FVector(0.f);//FVector with x,y,z = 0.f;
	float Deltatime = UGameplayStatics::GetWorldDeltaSeconds(this); //Get the deltatime, aka the time between each frame, in seconds

	//Adjust tank speed by deltatime (scale it to move the tank consistently in each frame) and Speed. Value is the input axis of keys W and S
	DeltaLocation.X += Value * Deltatime * MovementSpeed;
	AddActorLocalOffset(DeltaLocation, true); //bSweep = true prevents compenetrations if collision is enabled
}

//See "Move" function for the details...it's the same
void ATank::Turn(float Value) {
	FRotator DeltaRotation = FRotator(0.f);
	float Deltatime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw += Value * RotationSpeed * Deltatime;

	AddActorLocalRotation(DeltaRotation, true);
}