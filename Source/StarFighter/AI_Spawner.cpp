// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFighter.h"
#include "AI_Spawner.h"


// Sets default values
AAI_Spawner::AAI_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Number of current spawns and max spawns
	numSpawns = 0;
	maxSpawns = 2;

	// Timing variables
	timeSinceLastSpawn = 0.0f;
	maxTimeUntilSpawn = 15.0f;
	minTimeUntilSpawn = 5.0f;

	// Facing direction (for spawning)
	forwardVector = GetActorForwardVector();
}

// Called when the game starts or when spawned
void AAI_Spawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAI_Spawner::Tick( float deltaTime )
{
	Super::Tick(deltaTime);
	timeSinceLastSpawn += deltaTime;

	if (timeSinceLastSpawn >= minTimeUntilSpawn) {
		if (timeSinceLastSpawn >= maxTimeUntilSpawn) {
			// Check if can spawn
			if (numSpawns < maxSpawns) {
				// Spawn
				spawn();
				numSpawns++;
				timeSinceLastSpawn = 0.0f;
			}
		}
		// Determine if should spawn
	}
}

void AAI_Spawner::spawn() {
	AAI_Pilot* aiPilot = GetWorld()->SpawnActor<AAI_Pilot>(AAI_Pilot::StaticClass(), GetActorLocation() + forwardVector * 10.0f, FRotator::ZeroRotator);
	aiPilot->init(EShipsEnum::SHIP_TIEFIGHTER, GetActorLocation() + forwardVector * 10.0f, 3000.0f);
	spawns.Add(aiPilot);
}

