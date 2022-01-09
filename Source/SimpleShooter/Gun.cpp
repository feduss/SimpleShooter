// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Shoot() {
	if (ShootEffect != nullptr) {
		UGameplayStatics::SpawnEmitterAttached(ShootEffect, GunMesh, TEXT("MuzzleFlashSocket"));
	}

	APawn* ShooterCharacter = Cast<APawn>(GetOwner());
	if (ShooterCharacter != nullptr) {
		//Get player viewport (location and rotation are OUT var)
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			PlayerLocation,
			PlayerRotation
		);

		//Get end of raycast
		FVector End = PlayerLocation + (PlayerRotation.Vector() * Range);

		FHitResult Hit;

		//Raycast
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(
			Hit,
			PlayerLocation,
			End,
			ECollisionChannel::ECC_GameTraceChannel1 //Our custom trace channel "Bullet" in in this channel1
		);

		//Draw debug point in player viewport if hit something
		if (bSuccess) {
			FVector ImpactLocation = Hit.Location;
			FRotator ImpactRotation = (-PlayerRotation.Vector()).Rotation(); //The inverse rotation of the impact
			if (ImpactEffect != nullptr) {
				UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, ImpactLocation, ImpactRotation);
			}
		}
	}
}

