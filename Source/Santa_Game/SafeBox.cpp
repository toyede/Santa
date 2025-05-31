


#include "SafeBox.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
ASafeBox::ASafeBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SafeBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SafeBodyMesh"));
	SafeBodyMesh->SetupAttachment(RootComponent);

	SafeDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SafeDoorMesh"));
	SafeDoorMesh->SetupAttachment(SafeBodyMesh);

	KeypadAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("KeypadAttachPoint"));
	KeypadAttachPoint->SetupAttachment(SafeDoorMesh);
	KeypadAttachPoint->SetRelativeLocation(FVector(30.0f, 0.0f, 120.0f));

	bIsOpen = false; // 초기 상태는 닫혀 있음
	TargetYaw = 90.f; // 초기 목표 Yaw
	OpenSpeed = 45.f; // 문이 열리는 속도
	CurrentYaw = 0.f; // 현재 Yaw 초기화
}

// Called when the game starts or when spawned
void ASafeBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASafeBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpen)
	{
		float Step = OpenSpeed * DeltaTime;
		CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.0f); // 2.0f는 속도
		SafeDoorMesh->SetRelativeRotation(FRotator(0.0f, CurrentYaw, 0.0f));
	}
}

void ASafeBox::OpenDoor()
{
	if (!bIsOpen)
	{
		bIsOpen = true; // 문을 연다
		OnDoorOpened(); // 문이 열렸을 때 이벤트 호출
	}
}

