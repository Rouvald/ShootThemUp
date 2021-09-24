// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
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
    virtual void OnDeath();
};
