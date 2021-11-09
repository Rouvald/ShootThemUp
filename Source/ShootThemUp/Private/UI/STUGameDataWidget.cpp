// Shoot Them Up. All Rights Recerved


#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetCurrentRound() const
{
    const auto GameMode = GetGameModeBase();
    return GameMode ? GameMode->GetCurrentRound() : 0;
}
int32 USTUGameDataWidget::GetRoundsNum() const
{
    const auto GameMode = GetGameModeBase();
    return GameMode ? GameMode->GetRoundsNum() : 0;
}
int32 USTUGameDataWidget::GetRoundTime() const
{
    const auto GameMode = GetGameModeBase();
    return GameMode ? GameMode->GetRoundTime() : 0;
}
ASTUGameModeBase* USTUGameDataWidget::GetGameModeBase() const
{
    return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()): nullptr;
}
ASTUPlayerState* USTUGameDataWidget::GetPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}