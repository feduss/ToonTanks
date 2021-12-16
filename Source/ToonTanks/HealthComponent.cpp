// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	//Bind the event "take any damage" of the owner of this class to the function TakeDamage
	//OnTakeAnyDamage will be trigger by the event "damage event"
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);

	//Get the gamemode (useful to handle pawn death)
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this)); //GetGameMode is ok for single player game
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, 
	AController* Instigator, AActor* DamageCauser) {

	if (Damage > 0.f && DamagedActor != nullptr) {
		CurrentHealth -= Damage;
		if (CurrentHealth <= 0.f) {
			ToonTanksGameMode->ActorDied(DamagedActor);
		}
		//UE_LOG(LogTemp, Warning, TEXT("%s -> Damage: %f, Health: %f"), *GetOwner()->GetName(), Damage, CurrentHealth);
	}
	
}

