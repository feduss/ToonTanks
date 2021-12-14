// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Controller.h"

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
	//UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, %OtherComp: %s, HitResult: %s"), *OtherActor->GetName(), 
	//	*OtherComp->GetName(), *HitResult.GetActor()->GetName());

	auto MyOwner = GetOwner();
	if (MyOwner != nullptr) {
		AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
		UClass* DamageTypeClass = UDamageType::StaticClass();

		//If there is a damaged actor and if the damaged actor isn't ourself or our parent (there's no auto damaged lol)
		if (OtherActor != nullptr && OtherActor != this && OtherActor != MyOwner) {
			UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		}
	}

	this->Destroy();
}

