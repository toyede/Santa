

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SafeBox.generated.h"

UCLASS()
class SANTA_GAME_API ASafeBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASafeBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Safe")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Safe")
	void OnDoorOpened(); // 문이 열렸을 때 호출되는 이벤트

	UFUNCTION(BlueprintPure, Category = "Safe")
	bool IsDoorOpen() const { return bIsOpen; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Safe")
	USceneComponent* KeypadAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Safe")
	bool bIsOpen; // 상태 변수: 문이 열려 있는지 여부

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Safe")
	float TargetYaw;

	float OpenSpeed;
	float CurrentYaw;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SafeBodyMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SafeDoorMesh;



};
