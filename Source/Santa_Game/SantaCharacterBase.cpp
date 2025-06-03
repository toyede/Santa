
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"
#include "SantaCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

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

void ASantaCharacterBase::Move(const FInputActionValue& Value)
{
	// FInputActionValue에서 Axis2D꺼내와 X와Y입력으로 사용
	FVector2D InputValue = Value.Get<FVector2D>();
	
	// 컨트롤러 유효성 검사 및 실제 입력하고있는지 검사
	if (Controller != nullptr && (InputValue.X != 0.0f || InputValue.Y != 0.0f))
	{
		// Y축 추출
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		// X축 입력 처리
		if (InputValue.X != 0.0f)
		{
			const FVector RightDirection = UKismetMathLibrary::GetRightVector(YawRotation);
			AddMovementInput(RightDirection, InputValue.X);
		}

		// Y축 입력 처리
		if (InputValue.Y != 0.0f)
		{
			const FVector ForwardDirection = YawRotation.Vector();
			AddMovementInput(ForwardDirection, InputValue.Y);
		}

		OnMoved.Broadcast();
	}
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

		if (PlayerController != nullptr)
		{
			// 현재 로컬 플레이어에 붙어있는 EnhancedSubsystem을 가져옴
			UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
				if (EnhancedSubsystem != nullptr)
				{
					EnhancedSubsystem->AddMappingContext(IC_Character, 1);// IC_Character를 우선순위 1순위로 등록
				}
		}

		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ASantaCharacterBase::Move);
		EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

