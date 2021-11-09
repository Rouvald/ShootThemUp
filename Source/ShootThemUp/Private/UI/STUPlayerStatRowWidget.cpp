// Shoot Them Up. All Rights Recerved


#include "UI/STUPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Text) const
{
    if (!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerKills(const FText& Text) const
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerDeaths(const FText& Text) const
{
    if (!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerTeamID(const FText& Text) const
{
    if (!TeamIDTextBlock) return;
    TeamIDTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisible(const bool Visible) const
{
    if (!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatRowWidget::SetTeamColorImage(const FLinearColor& Color) const
{
    if(!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
