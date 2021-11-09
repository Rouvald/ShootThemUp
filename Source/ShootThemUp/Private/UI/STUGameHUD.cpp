// Shoot Them Up. All Rights Recerved


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/STUBaseWidget.h"
#include "STUGameModeBase.h"


DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);


void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();

    //DrawCrossHAir();
}

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<USTUBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<USTUBaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<USTUBaseWidget>(GetWorld(), GameOverWidgetClass));

    for (const auto GameWidget : GameWidgets)
    {
        const auto GameWidgetCreate = GameWidget.Value;
        if(GameWidgetCreate)
        {
            GameWidgetCreate->AddToViewport();
            GameWidgetCreate->SetVisibility(ESlateVisibility::Hidden);
        }
    }

    if(GetWorld())
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMatchStateChange.AddUObject(this, &ASTUGameHUD::OnGameStateChange);
        }
    }
}

void ASTUGameHUD::OnGameStateChange(ESTUMatchState NewState)
{
    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if(GameWidgets.Contains(NewState))
    {
        CurrentWidget = GameWidgets[NewState];
    }
    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }
    UE_LOG(LogSTUGameHUD, Display, TEXT("Match state is change: %s"), *UEnum::GetValueAsString(NewState));
}


void ASTUGameHUD::DrawCrossHAir()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThikness = 2.0f;
    const FLinearColor LineColor = FColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThikness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThikness);
}
