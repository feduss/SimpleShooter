// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind "W" and "S" to a function
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpGamepad"), this, &AShooterCharacter::LookUpGamepad);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookRightGamepad"), this, &AShooterCharacter::LookRightGamepad);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Jump);

}

void AShooterCharacter::MoveForward(float AxisValue) {
	//AddMovementInput is a method of Character
	//GetActorForwardVector get the forward vector of the character
	//AxisValue is the value of "W" and "S"
	Super::AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue) {
	Super::AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue) {
	//AddMovementInput is a method of Character
	//GetActorForwardVector get the forward vector of the character
	//AxisValue is the value of "W" and "S"
	if (bInvertedAxis) {
		Super::AddControllerPitchInput(-AxisValue);
	}
	else {
		Super::AddControllerPitchInput(AxisValue);
	}

}

void AShooterCharacter::LookUpGamepad(float AxisValue) {
	//The rotation with the controller (Gamepad) is framerate dependent (the mouse rotation not)
	//so, we need a framerate indipendent var (RotationRate)
	//and the delta time, the time between each frames
	if (bInvertedAxis) {
		Super::AddControllerPitchInput(-AxisValue * RotationRateUp * GetWorld()->GetDeltaSeconds());
	}
	else {
		Super::AddControllerPitchInput(AxisValue * RotationRateUp * GetWorld()->GetDeltaSeconds());
	}

}

void AShooterCharacter::LookRight(float AxisValue) {
	Super::AddControllerYawInput(AxisValue);
}

void AShooterCharacter::LookRightGamepad(float AxisValue) {
	//The rotation with the controller (Gamepad) is framerate dependent (the mouse rotation not)
	//so, we need a framerate indipendent var (RotationRate)
	//and the delta time, the time between each frames
	Super::AddControllerYawInput(AxisValue * RotationRateRight * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::Jump() {
	if (!bIsJumping) {
		bIsJumping = true;

		Super::Jump();

		bIsJumping = false;
	}
}

