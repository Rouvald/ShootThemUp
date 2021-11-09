// Shoot Them Up. All Rights Recerved


#include "Menu/STUMenuPlayerController.h"

void ASTUMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}