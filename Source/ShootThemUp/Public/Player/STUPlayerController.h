// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUCoreTypes.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
    GENERATED_BODY()

    public:
    ASTUPlayerController();

    protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
    USTURespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;

    private:
    void OnPauseGame();
    void OnMatchStateChange(ESTUMatchState NewState);
    
};
