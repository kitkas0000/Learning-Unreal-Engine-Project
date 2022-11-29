#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyProject/Types/SpeedMode.h"
#include "MyCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UMyComponent;
UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();
	// virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void AttackButtonPressed();
	virtual void SprintButtonPressed();

	// Released
	virtual void SprintButtonReleased();
	// Axises
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void LookUp(float Value);
	virtual void Turn(float Value);


private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY()
	ESpeedMode SpeedMode;

	UPROPERTY(EditAnywhere, Category= Movement);
	float SprintSpeed = 800.f;
	UPROPERTY(EditAnywhere, Category= Movement);
	float JogSpeed = 400.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"));
	UMyComponent* MyComponent;
	//Setter and getter
public:	
	FORCEINLINE UFUNCTION(BlueprintCallable) UMyComponent* GetCombatComponent() const {	return MyComponent;	}

};
