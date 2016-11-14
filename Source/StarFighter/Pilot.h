#pragma once

#include "GameFramework/Character.h"
#include "Pilot.generated.h"

UENUM(BlueprintType)
enum class EShipsEnum : uint8 {
	SHIP_DEFAULT		UMETA(DisplayName = "Default"),
	SHIP_TIEFIGHTER		UMETA(DisplayName = "Tie Fighter"),
	SHIP_DARKFIGHTER	UMETA(DisplayName = "Dark Fighter"),
	SHIP_FRIGATE		UMETA(DisplayName = "Frigate"),
	SHIP_MK6			UMETA(DisplayName = "MK6")
};

UCLASS(BlueprintType)
class STARFIGHTER_API APilot : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APilot();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
protected:
	// Which model to use
	EShipsEnum shipModel;

	// The model
	UStaticMeshComponent* shipMesh;

	// Forward vector for the pilot
	FVector forwardVector;

	// Up vector for the pilot
	FVector upVector;

	// Loads the correct ship mesh
	void loadShip();
};