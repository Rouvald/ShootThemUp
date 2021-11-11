// Shoot Them Up. All Rights Recerved


#include "Sound/STUSoundFuncLib.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUSoundFuncLib, All, All);

void USTUSoundFuncLib::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if(!SoundClass) return;

    SoundClass->Properties.Volume = Volume;
    UE_LOG(LogSTUSoundFuncLib, Display, TEXT("%s : %f"), *SoundClass->GetName(), Volume);
}

void USTUSoundFuncLib::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if(!SoundClass) return;

    const auto NextVolume = SoundClass->Properties.Volume >0.0f ? 0.0f : 1.0f;

    SetSoundClassVolume(SoundClass, NextVolume);
}