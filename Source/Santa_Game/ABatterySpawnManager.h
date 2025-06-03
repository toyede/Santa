

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABatterySpawnManager.generated.h"

class ATargetPoint;

UCLASS()
class SANTA_GAME_API AABatterySpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABatterySpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> BatteryClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<ATargetPoint*> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 NumBatterisToSpawn = 2;

	void SpawnBatteries();
};
