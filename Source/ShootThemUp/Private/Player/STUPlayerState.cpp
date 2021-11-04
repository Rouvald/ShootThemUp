// Shoot Them Up. All Rights Recerved


#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePlayerState, All, All);

void ASTUPlayerState::LogInfo()
{
    UE_LOG(LogBasePlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}