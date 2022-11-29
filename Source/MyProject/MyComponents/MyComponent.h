
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyProject/Types/CombatState.h"
#include "MyComponent.generated.h"

class ACharacter;
class UAnimMontage;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UMyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyComponent();
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void RequestAttack();

	void PlayAnimMontage(UAnimMontage* MontageToPlay);

	UFUNCTION(BlueprintCallable)
	void ResetCombat();
protected:
	virtual void BeginPlay() override;
	virtual void Attack();

private:
	UPROPERTY()
	ECombatState CombatState;

	UPROPERTY(EditAnywhere, Category= Animations)
	TArray<UAnimMontage*> AttackAnimMontages;

	UPROPERTY()
	ACharacter* Character;

	// Getters and Setters
public:
	FORCEINLINE void SetCharacter(ACharacter* Value) {	Character = Value;	}
		
};
