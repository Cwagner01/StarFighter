// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFighter.h"
#include "Pilot.h"


// Sets default values
APilot::APilot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	shipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship Mesh"));

	shipModel = EShipsEnum::SHIP_DEFAULT;
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
	UStaticMesh* tmpMesh;

	switch (shipModel) {
	case EShipsEnum::SHIP_DARKFIGHTER:
		tmpMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Ships/dark_fighter_6/dark_fighter_6")));
		forwardVector = FVector(-1.0f, 0.0f, 0.0f);
		upVector = FVector(0.0f, 0.0f, 1.0f);
		break;
	case EShipsEnum::SHIP_FRIGATE:
		tmpMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Ships/space_frigate_6/space_frigate_6")));
		forwardVector = FVector(-1.0f, 0.0f, 0.0f);
		upVector = FVector(0.0f, 0.0f, 1.0f);
		break;
	case EShipsEnum::SHIP_MK6:
		tmpMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Ships/SciFi_Fighter-MK6-OBJ/MK6_OBJ")));
		forwardVector = FVector(0.0f, 0.0f, 1.0f);
		upVector = FVector(1.0f, 0.0f, 0.0f);
		break;
	case EShipsEnum::SHIP_TIEFIGHTER:
	case EShipsEnum::SHIP_DEFAULT:
	default:
		tmpMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Ships/TieFighter/TieFighter")));
		forwardVector = FVector(-1.0f, 0.0f, 0.0f);
		upVector = FVector(0.0f, 0.0f, 1.0f);
		break;
	}
	RootComponent = shipMesh;
	shipMesh->SetStaticMesh(tmpMesh);
	shipMesh->RegisterComponent();
}

