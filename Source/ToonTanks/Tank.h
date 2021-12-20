// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	APlayerController* GetTankPlayerController() const { return PlayerController; }

	bool bAlive = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MovementSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float RotationSpeed = 20.f;

	//Child of AController, the invisible object that possesses the pawn
	APlayerController* PlayerController = nullptr;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(float Value);
	void Turn(float Value);
	void Fire();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();
};
