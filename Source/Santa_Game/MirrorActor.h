

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MirrorActor.generated.h"

UCLASS()
class SANTA_GAME_API AMirrorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMirrorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Mirror")
	void BreakMirror();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MirrorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mirror")
	float MaxDistanceToPlayer = 500.0f; // Maximum distance to consider the player looking at the mirror

private:
	bool bIsBeingLookedAt;
	bool bIsBroken;
	float TimeBeingLookedAt;

	void CheckPlayerGaze();

};
