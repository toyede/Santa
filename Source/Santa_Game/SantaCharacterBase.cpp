
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SantaCharacterBase.h"

// 생성자
ASantaCharacterBase::ASantaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// 처음 시작했을 때 수행할 것들
void ASantaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// 매프레임마다 수행할 것들
void ASantaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Input 바인드
void ASantaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 플레이어 입력 컴포넌트를 EngancedInput으로 사용하게끔 형변환
	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedPlayerInputComponent != nullptr)
	{
		// 컨트롤러 속성을 APlayerController로 형변환
		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		// 현재 로컬 플레이어에 붙어있는 EnhancedSubsystem을 가져옴
		UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		EnhancedSubsystem->AddMappingContext(IC_Character, 1);// IC_Character를 우선순위 1순위로 등록
		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASantaCharacterBase::Move); // IA_Move가 발생했을 때 
	}
}

