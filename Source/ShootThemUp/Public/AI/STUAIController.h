// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
    GENERATED_BODY()

public:
    ASTUAIController();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    USTUAIPerceptionComponent* STUAIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    AActor* GetFocusOnActor();
};
