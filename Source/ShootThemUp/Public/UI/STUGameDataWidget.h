// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"


class ASTUGameModeBase;
class ASTUPlayerState;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

    public:
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetCurrentRound() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRoundTime() const;

    private:

    ASTUGameModeBase* GetGameModeBase() const;
    ASTUPlayerState* GetPlayerState() const;
};
