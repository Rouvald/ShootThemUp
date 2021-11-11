// Shoot Them Up. All Rights Recerved


#include "STUGameInstance.h"
#include "Sound/STUSoundFuncLib.h"

void USTUGameInstance::ToggleVolume()
{
    USTUSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}