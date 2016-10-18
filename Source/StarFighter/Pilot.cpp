// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFighter.h"
#include "Pilot.h"


// Sets default values
APilot::APilot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APilot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APilot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APilot::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void APilot::loadShip() {
	switch (shipModel) {
	case EShipsEnum::SHIP_DARKFIGHTER:
		break;
	case EShipsEnum::SHIP_TIEFIGHTER:
		break;
	case EShipsEnum::SHIP_FRIGATE:
		break;
	case EShipsEnum::SHIP_DEFAULT:
	default:
		break;
	}
}

