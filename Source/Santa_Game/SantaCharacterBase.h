

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SantaCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovedSignature);

UCLASS()
class SANTA_GAME_API ASantaCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASantaCharacterBase();

	UPROPERTY(EditAnywhere, Category = Input) 
	class UInputMappingContext* IC_Character;

	UPROPERTY(EditAnywhere, Category = Input) 
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Jump;

	UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMovedSignature OnMoved;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
