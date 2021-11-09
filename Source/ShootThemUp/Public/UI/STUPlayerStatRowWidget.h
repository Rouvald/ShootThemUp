// Shoot Them Up. All Rights Recerved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"


class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerName(const FText& Text) const;
    void SetPlayerKills(const FText& Text) const;
    void SetPlayerDeaths(const FText& Text) const;
    void SetPlayerTeamID(const FText& Text) const;
    void SetPlayerIndicatorVisible(const bool Visible) const;
    void SetTeamColorImage(const FLinearColor& Color) const; 

protected:
    UPROPERTY(meta=(BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* TeamIDTextBlock;

    UPROPERTY(meta=(BindWidget))
    UImage* PlayerIndicatorImage;

    UPROPERTY(meta=(BindWidget))
    UImage* TeamImage;
};
