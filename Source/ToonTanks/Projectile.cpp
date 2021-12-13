// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));

	RootComponent = Projectile;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projecile Movement"));

	ProjectileMovementComponent->InitialSpeed = 1500.f;
	ProjectileMovementComponent->MaxSpeed = 1500.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	//multi cast delegate to bind the hit event of this class to a function
	Projectile->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* PrimitiveComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector Impulse, const FHitResult& HitResult) {
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, %OtherComp: %s, HitResult: %s"), *OtherActor->GetName(), 
		*OtherComp->GetName(), *HitResult.GetActor()->GetName());
}

