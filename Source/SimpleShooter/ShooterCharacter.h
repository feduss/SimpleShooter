// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpGamepad(float AxisValue);
	void LookRight(float AxisValue);
	void LookRightGamepad(float AxisValue);
	void Jump();

	bool bInvertedAxis = false;
	bool bIsJumping = false;

	UPROPERTY(EditAnywhere)
	float RotationRateUp = 100.f;

	UPROPERTY(EditAnywhere)
	float RotationRateRight = 100.f;

	//The gun class, not editabled at runtime (EditDefaultOnly)
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	//The gun pointer
	UPROPERTY()
	class AGun* Gun = nullptr;
};
