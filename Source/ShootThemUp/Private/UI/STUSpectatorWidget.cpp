// Shoot Them Up. All Rights Recerved


#include "UI/STUSpectatorWidget.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"

int32 USTUSpectatorWidget::GetRespawnTime() const
{
    const auto RespawnComponent = GetRespawnComponent();

    return RespawnComponent ? RespawnComponent->GetRespawnTime() : 0;
}

int32 USTUSpectatorWidget::GetRoundTime() const
{
    const auto GameMode = GetGameModeBase();
    return GameMode ? GameMode->GetRoundTime() : 0;
}

bool USTUSpectatorWidget::CheckRespawnTimerIsActive() const
{
    const auto RespawnComponent = GetRespawnComponent();

    return RespawnComponent ? RespawnComponent->CheckRespawnTimerIsActive() : false;
}

USTURespawnComponent* USTUSpectatorWidget::GetRespawnComponent() const
{
    return GetOwningPlayer() ? STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer()) : nullptr;
}

ASTUGameModeBase* USTUSpectatorWidget::GetGameModeBase() const
{
    return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}
