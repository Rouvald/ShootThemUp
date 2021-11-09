// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
    GENERATED_BODY()

public:
    ASTUAICharacter(const FObjectInitializer& ObjInit);

    //UBehaviorTree* GetBehaviorTreeAsset () const {return BehaviorTreeAsset;}

    //protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    UBehaviorTree* BehaviorTreeAsset;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Component")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    float HealthWidgetVisibilityDistance = 1500.0f;
    
    virtual void BeginPlay() override;
    
    virtual void OnDeath();

    virtual void OnHealthChanged(float Health, float HealthDelta) override;

    private:
    FTimerHandle CheckHealthWidgetVisibility;

    void UpdateHealthWidgetVisibility();
};
