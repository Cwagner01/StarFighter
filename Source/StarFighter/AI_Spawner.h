#include "GameFramework/Actor.h"
#include "AI_Pilot.h"
#include "AI_Spawner.generated.h"

UCLASS()
class STARFIGHTER_API AAI_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAI_Spawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	// Number of current spawns and max spawns
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 numSpawns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 maxSpawns;

	// Timing variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float timeSinceLastSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxTimeUntilSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float minTimeUntilSpawn;

	// Facing direction (for spawning)
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector forwardVector;

	// Array of AI pilot spawns
	TArray<AAI_Pilot*> spawns;
protected:
	void spawn();
};
