// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUSpectatorWidget.generated.h"

class USTURespawnComponent;
class ASTUGameModeBase;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

    public:

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRespawnTime() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRoundTime() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    bool CheckRespawnTimerIsActive() const;

    private:
    USTURespawnComponent* GetRespawnComponent() const;
    ASTUGameModeBase* GetGameModeBase() const;
};
