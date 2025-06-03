


#include "ABatterySpawnManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AABatterySpawnManager::AABatterySpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AABatterySpawnManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnBatteries();
}

void AABatterySpawnManager::SpawnBatteries()
{
	if (!BatteryClass || SpawnPoints.Num() < NumBatterisToSpawn)
	{
		return;
	}
	TArray<int32> Indices;
	for (int32 i = 0; i < SpawnPoints.Num(); ++i)
	{
		Indices.Add(i);
	}
	Indices.Sort([](const int32 A, const int32 B) { return FMath::RandBool(); });

	for (int32 i = 0; i < NumBatterisToSpawn; ++i)
	{
		ATargetPoint* Point = SpawnPoints[Indices[i]];
		if (Point)
		{
			GetWorld()->SpawnActor<AActor>(BatteryClass, Point->GetActorLocation(), Point->GetActorRotation());
		}
	}
}

// Called every frame

void AABatterySpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

