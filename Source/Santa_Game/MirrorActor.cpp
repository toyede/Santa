


#include "MirrorActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

// Sets default values
AMirrorActor::AMirrorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);

	MirrorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MirrorMesh"));
	MirrorMesh->SetupAttachment(SceneRoot);
	bIsBeingLookedAt = false;
	bIsBroken = false;
	TimeBeingLookedAt = 0.0f;

}

// Called when the game starts or when spawned
void AMirrorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMirrorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsBroken)
	{
		return; // If the mirror is broken, skip further processing
	}

	CheckPlayerGaze();

	if (bIsBeingLookedAt)
	{
		TimeBeingLookedAt += DeltaTime;
		if (TimeBeingLookedAt >= 3.0f) // 3 seconds threshold
		{
			BreakMirror();
			bIsBroken = true; // Set the mirror as broken
			TimeBeingLookedAt = 0.0f; // Reset the timer after breaking the mirror
		}
	}
	else
	{
		TimeBeingLookedAt = 0.0f; // Reset if not being looked at
	}

}

void AMirrorActor::CheckPlayerGaze()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController)
	{
		return; // No player controller found
	}

	FVector PlayerLocation;
	FRotator PlayerRotation;
	PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	FVector ViewDirection = PlayerRotation.Vector();
	FVector DirectionToMirror = (GetActorLocation() - PlayerLocation).GetSafeNormal();

	float DistanceToPlayer = FVector::Dist(PlayerLocation, GetActorLocation());

	if (DistanceToPlayer > MaxDistanceToPlayer)
	{
		bIsBeingLookedAt = false; // Player is too far away to be looking at the mirror
		return;
	}

	float ViewDot = FVector::DotProduct(ViewDirection, DirectionToMirror);

	FVector MirrorForward = GetActorForwardVector();
	float ReflectDot = FVector::DotProduct(-DirectionToMirror, MirrorForward);

	bIsBeingLookedAt = (ViewDot > 0.8f && ReflectDot > 0.95f);


}

