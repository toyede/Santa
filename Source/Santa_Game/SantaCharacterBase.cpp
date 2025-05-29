


#include "SantaCharacterBase.h"

// 생성자
ASantaCharacterBase::ASantaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// 처음 시작했을 때 수행할 것 들
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

}

