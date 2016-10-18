#pragma once

#include "GameFramework/Character.h"
#include "Pilot.h"
#include "AI_Pilot.generated.h"

UENUM(BlueprintType)
enum class EAI_StatesEnum : uint8 {
	AI_DEFAULT	UMETA(DisplayName = "Default"),
	AI_IDLE		UMETA(DisplayName = "Idle"),
	AI_PATROL	UMETA(DisplayName = "Patrol"),
	AI_ENGAGE	UMETA(DisplayName = "Engage")
};

UCLASS(BlueprintType)
class STARFIGHTER_API AAI_Pilot : public APilot
{
	GENERATED_BODY()

public:
	// Spawn location
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector spawnLocation;

	// Patrol radius
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float patrolRadius;

	// Sets default values for this character's properties
	AAI_Pilot();

	// Initializes the AI pilot with necessary information
	void init(EShipsEnum shipModel, FVector spawnLoc, float pRadius);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
protected:
	class APatrolVolume : public AVolume
	{
	public:
		float minX;
		float maxX;
		float minY;
		float maxY;
		float minZ;
		float maxZ;

		APatrolVolume(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
			this->minX = minX;
			this->maxX = maxX;
			this->minY = minY;
			this->maxY = maxY;
			this->minZ = minY;
			this->maxZ = maxY;
		};

		void setBounds(float minX, float maxX, float minY, float maxY, float minZ, float maxZ) {
			this->minX = minX;
			this->maxX = maxX;
			this->minY = minY;
			this->maxY = maxY;
			this->minZ = minY;
			this->maxZ = maxY;
		};

		bool contains(FVector position) {
			if (position.X <= maxX && position.X >= minX) {
				if (position.Y <= maxY && position.Y >= minY) {
					if (position.Z <= maxZ && position.Z >= minZ) {
						return true;
					}
				}
			}
			return false;
		};
	};

	// Which ship to use for the model
	EShipsEnum shipModel;

	// Current AI state
	EAI_StatesEnum aiState;

	// Current location to move to
	FVector goalLocation;

	// Patrol volumes
	TArray<AAI_Pilot::APatrolVolume*> patrolVolumes;	

	// Generates patrol volumes based on spawn location
	void generatePatrolVolumes();

	// Determines which patrol volume the AI_Pilot is in, -1 if none
	int determinePatrolVolume();

	// Determines where to go next
	FVector determineNextDestination();

	// Generates a location within the volume
	FVector generateGoalLocation(int patrolVolume);

	// Patrol around the patrol volumes
	void patrol();

	// Engage a stimulus
	void engage();

	// Idle at a location
	void idle();
};