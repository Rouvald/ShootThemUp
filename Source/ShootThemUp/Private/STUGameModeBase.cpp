// Shoot Them Up. All Rights Recerved

#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"
#include "EngineUtils.h"
#include "Player/STUPlayerState.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGameMode, All, All);

constexpr static int32 MinRespawnTime = 10;

ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
    PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();
    CurrentRound = 1;
    StartRound();
    SetMatchState(ESTUMatchState::InProgress);
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto PlayerAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(PlayerAIController);
    }
}

void ASTUGameModeBase::StartRound()
{
    if (!GetWorld()) return;

    RoundCountDown = GameData.RoundTime;
    GetWorld()->GetTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate, 1.0f, true);
}

void ASTUGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogBaseGameMode, Display, TEXT("Time: %i, Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);
    if (--RoundCountDown == 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void ASTUGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void ASTUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTUGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    int32 BotNameValue = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
        if (!PlayerState) continue;

        PlayerState->SetTeamId(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot_" + FString::FromInt(BotNameValue++));
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    UE_LOG(LogBaseGameMode, Warning, TEXT("No clor for team id: %i, set to default color &s"), TeamID,
        *(GameData.DefaultTeamColor.ToString()));
    return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* Controller) const
{
    if (!Controller) return;

    const auto Character = Cast<ASTUBaseCharacter>(Controller->GetPawn());
    if (!Character) return;

    const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
    if (!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTUGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    const auto KillerPlayerState = KillerController ? KillerController->GetPlayerState<ASTUPlayerState>() : nullptr;
    const auto VictimPlayerState = VictimController ? VictimController->GetPlayerState<ASTUPlayerState>() : nullptr;

    if (KillerPlayerState && KillerPlayerState->GetTeamId() != VictimPlayerState->GetTeamId())
    {
        KillerPlayerState->AddKill();
    }
    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }
    StartRespawn(VictimController);
}

void ASTUGameModeBase::LogPlayerInfo() const
{
    if (!GetWorld()) return;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
        if (!PlayerState) continue;

        PlayerState->LogInfo();
    }
}

void ASTUGameModeBase::StartRespawn(AController* Controller) const
{
    const bool RespawnAvailable = RoundCountDown > MinRespawnTime + GameData.RespawnTime;
    if (!RespawnAvailable) return;

    const auto RespawnComponents = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);
    if (!RespawnComponents) return;

    RespawnComponents->Respawn(GameData.RespawnTime);
}

void ASTUGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

void ASTUGameModeBase::GameOver()
{
    for (const auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
    UE_LOG(LogBaseGameMode, Display, TEXT("==========GAME OVER=========="));
    LogPlayerInfo();

    SetMatchState(ESTUMatchState::GameOver);
}

void ASTUGameModeBase::SetMatchState(ESTUMatchState NewState)
{
    if (NewState == MatchState) return;

    MatchState = NewState;
    OnMatchStateChange.Broadcast(MatchState);
}

bool ASTUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (PauseSet)
    {
        SetMatchState(ESTUMatchState::Pause);
    }

    return PauseSet;
}

bool ASTUGameModeBase::ClearPause()
{
    const auto PauseClear = Super::ClearPause();

    if (PauseClear)
    {
        SetMatchState(ESTUMatchState::InProgress);
    }

    return PauseClear;
}
