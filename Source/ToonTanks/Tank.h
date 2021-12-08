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
protected:

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MovementSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float RotationSpeed = 20.f;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(float Value);
	void Turn(float Value);
public:
	
};
