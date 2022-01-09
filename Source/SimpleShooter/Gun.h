// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void Shoot(); //Pull the trigger

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* GunMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* ShootEffect = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* ImpactEffect = nullptr;

	FVector PlayerLocation;
	FRotator PlayerRotation;

	UPROPERTY(EditAnywhere)
	float Range = 3000.f;
};
