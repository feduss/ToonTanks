// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#define out

ATank::ATank() {
	//Create a USpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	SpringArmComponent->SetupAttachment(RootComponent);

	//Create a UCameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

	CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	//Attach CameraComponent to SpringArmComponent as child
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//The player controller will be useful to get the hitresult of 2d mouse movement into the 3d map
	PlayerController = Cast<APlayerController>(GetController());

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController != nullptr) {
		FHitResult HitResult;

		//Get HitResult from a mouse linetrace
		bool hit = PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility, //Hit object the block visibility channel (aka linetrace?)
			false, //bTraceComplex false = 
			out HitResult
			);

		if (hit) {
			/*DrawDebugSphere(
				GetWorld(),
				HitResult.ImpactPoint, //center
				10.f,				   //radius of the sphere
				12,                    //number of segments of the sphere
				FColor::Red,
				false,                 //percistent false
				-1.0f                  //lifetime: 1 frame
			);*/
			RotateCannon(HitResult.ImpactPoint);

		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is null"));
	}

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind axis "MoveForward" to function Move
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);

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

void ATank::Fire() {
	InstantiateProjectile();
}