// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFighter.h"
#include "AI_Pilot.h"

// Sets default values
AAI_Pilot::AAI_Pilot() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	shipModel = EShipsEnum::SHIP_DEFAULT;
	loadShip();

	aiState = EAI_StatesEnum::AI_DEFAULT;

	spawnLocation = FVector(0.0f, 0.0f, 0.0f);

	patrolRadius = 1250.0f;
}

void AAI_Pilot::init(EShipsEnum shipModel, FVector spawnLoc, float pRadius) {
	this->shipModel = shipModel;
	loadShip();

	spawnLocation = spawnLoc;

	patrolRadius = pRadius;
}

// Called when the game starts or when spawned
void AAI_Pilot::BeginPlay()
{
	Super::BeginPlay();

	generatePatrolVolumes();

	goalLocation = determineNextDestination();
}

// Called every frame
void AAI_Pilot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	switch (aiState) {
	case EAI_StatesEnum::AI_PATROL:
		patrol();
		break;
	case EAI_StatesEnum::AI_ENGAGE:
		engage();
		break;
	case EAI_StatesEnum::AI_IDLE:
	case EAI_StatesEnum::AI_DEFAULT:
	default:
		idle();
		break;
	}
}

// Called to bind functionality to input
void AAI_Pilot::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AAI_Pilot::generatePatrolVolumes() {
	UWorld* const World = GetWorld();
	if (World) {
		// Generate patrol volume 0 (top right neg depth)
		AAI_Pilot::APatrolVolume* volume0 = GetWorld()->SpawnActor<AAI_Pilot::APatrolVolume>(AAI_Pilot::APatrolVolume::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		volume0->setBounds(
			spawnLocation.X,
			spawnLocation.X + patrolRadius,
			spawnLocation.Y - patrolRadius,
			spawnLocation.Y,
			spawnLocation.Z,
			spawnLocation.Z + patrolRadius
		);

		// Generate patrol volume 1 (top left neg depth)
		AAI_Pilot::APatrolVolume* volume1 = GetWorld()->SpawnActor<AAI_Pilot::APatrolVolume>(AAI_Pilot::APatrolVolume::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		volume1->setBounds(
			spawnLocation.X - patrolRadius, 
			spawnLocation.X, 
			spawnLocation.Y - patrolRadius, 
			spawnLocation.Y, 
			spawnLocation.Z, 
			spawnLocation.Z + patrolRadius
		);

		// Generate patrol volume 2 (top left pos depth)
		AAI_Pilot::APatrolVolume* volume2 = GetWorld()->SpawnActor<AAI_Pilot::APatrolVolume>(AAI_Pilot::APatrolVolume::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		volume2->setBounds(
			spawnLocation.X - patrolRadius, 
			spawnLocation.X, 
			spawnLocation.Y, 
			spawnLocation.Y + patrolRadius, 
			spawnLocation.Z, 
			spawnLocation.Z + patrolRadius
		);

		// Generate patrol volume 3 (top right pos depth)
		AAI_Pilot::APatrolVolume* volume3 = GetWorld()->SpawnActor<AAI_Pilot::APatrolVolume>(AAI_Pilot::APatrolVolume::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		volume3->setBounds(
			spawnLocation.X, 
			spawnLocation.X + patrolRadius, 
			spawnLocation.Y, 
			spawnLocation.Y + patrolRadius, 
			spawnLocation.Z, 
			spawnLocation.Z + patrolRadius
		);

		// Generate patrol volume 4 (bottom right neg depth)
		AAI_Pilot::APatrolVolume* volume4 = GetWorld()->SpawnActor<AAI_Pilot::APatrolVolume>(AAI_Pilot::APatrolVolume::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		volume4->setBounds(
			spawnLocation.X, 
			spawnLocation.X + patrolRadius, 
			spawnLocation.Y - patrolRadius, 
			spawnLocation.Y, 
			spawnLocation.Z - patrolRadius, 
			spawnLocation.Z
		);

		// Generate patrol volume 5 (bottom left neg depth)
		AAI_Pilot::APatrolVolume* volume5 = GetWorld()->SpawnActor<AAI_Pilot::APatrolVolume>(AAI_Pilot::APatrolVolume::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		volume5->setBounds(
			spawnLocation.X - patrolRadius, 
			spawnLocation.X, 
			spawnLocation.Y - patrolRadius, 
			spawnLocation.Y, 
			spawnLocation.Z - patrolRadius, 
			spawnLocation.Z
		);

		// Generate patrol volume 6 (bottom left pos depth)
		AAI_Pilot::APatrolVolume* volume6 = GetWorld()->SpawnActor<AAI_Pilot::APatrolVolume>(AAI_Pilot::APatrolVolume::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		volume6->setBounds(
			spawnLocation.X - patrolRadius, 
			spawnLocation.X, 
			spawnLocation.Y, 
			spawnLocation.Y + patrolRadius, 
			spawnLocation.Z - patrolRadius, 
			spawnLocation.Z
		);

		// Generate patrol volume 7 (bottom right pos depth)
		AAI_Pilot::APatrolVolume* volume7 = GetWorld()->SpawnActor<AAI_Pilot::APatrolVolume>(AAI_Pilot::APatrolVolume::StaticClass(), spawnLocation, FRotator::ZeroRotator);
		volume7->setBounds(
			spawnLocation.X, 
			spawnLocation.X + patrolRadius, 
			spawnLocation.Y, 
			spawnLocation.Y + patrolRadius, 
			spawnLocation.Z - patrolRadius, 
			spawnLocation.Z
		);

		// Add volumes to list
		patrolVolumes.Add(volume0);
		patrolVolumes.Add(volume1);
		patrolVolumes.Add(volume2);
		patrolVolumes.Add(volume3);
		patrolVolumes.Add(volume4);
		patrolVolumes.Add(volume5);
		patrolVolumes.Add(volume6);
		patrolVolumes.Add(volume7);
	}
}

int AAI_Pilot::determinePatrolVolume()
{
	FVector currLocation = GetActorLocation();

	for (int i = 0; i < patrolVolumes.Num(); i++) {
		if (patrolVolumes[i]->contains(currLocation)) {
			return i;
		}
	}
	return -1;
}

FVector AAI_Pilot::determineNextDestination()
{
	int currVolume = determinePatrolVolume();
	switch (currVolume) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		return generateGoalLocation(currVolume + 1);
	case 7:
	default:
		return generateGoalLocation(0);
	}
}

FVector AAI_Pilot::generateGoalLocation(int patrolVolume)
{
	FVector goalLocation = GetActorLocation() + GetActorForwardVector()*2.0;
	if (patrolVolume >= 0 && patrolVolume <= patrolVolumes.Num()) {
		goalLocation.X = ((FMath::RandRange(0, 100) / 100) * patrolVolumes[patrolVolume]->maxX) + patrolVolumes[patrolVolume]->minX;
		goalLocation.Y = ((FMath::RandRange(0, 100) / 100) * patrolVolumes[patrolVolume]->maxY) + patrolVolumes[patrolVolume]->minY;
		goalLocation.Z = ((FMath::RandRange(0, 100) / 100) * patrolVolumes[patrolVolume]->maxZ) + patrolVolumes[patrolVolume]->minZ;
	}
	return goalLocation;
}

void AAI_Pilot::idle() {
	// Do nothing for now
	aiState = EAI_StatesEnum::AI_PATROL;
}

void AAI_Pilot::patrol() {
	float distanceToGoal = 0.0f;
	FVector currLocation = GetActorLocation();

	// Check perception
	// If continue patrolling, check goal
	distanceToGoal = FVector::Dist(currLocation, goalLocation);

	// If close to goal, set next goal
	if (FMath::Abs(distanceToGoal) <= 5.0) {
		goalLocation = determineNextDestination();
	}

	// Move towards goal
	SetActorLocation(currLocation + (GetActorForwardVector()*2.0));
	// If not continue patrolling, determine next move
}

void AAI_Pilot::engage() {
	// Do nothing for now
}
