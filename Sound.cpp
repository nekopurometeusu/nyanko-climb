#include"Sound.h"
#include "Player.h"

Sound::Sound()
{
    isMainthemaHandle = LoadSoundMem("sound/Cooking-Banana.mp3");
    isLastspurtHandle = LoadSoundMem("sound/Melon-Beat-End-Roll.mp3");
    isUpsoundHandle = LoadSoundMem("sound/ƒpƒpƒb.mp3");
    isDownsoundHandle = LoadSoundMem("sound/ƒqƒ…[ƒ“‚Æ—‰º.mp3");
    isCatvoiceHandle = LoadSoundMem("sound/”L‚Ì–Â‚«º1.mp3");
    isClapHandle = LoadSoundMem("sound/‘å¨‚Å”è.mp3");
    isLastnoticeHandle = LoadSoundMem("sound/Œx‰¹2.mp3");
    ChangeVolumeSoundMem(45,isMainthemaHandle);
    ChangeVolumeSoundMem(45, isLastspurtHandle);
    ChangeVolumeSoundMem(90, isUpsoundHandle);
    ChangeVolumeSoundMem(90, isDownsoundHandle);
    ChangeVolumeSoundMem(90, isCatvoiceHandle);
}

Sound::~Sound()
{
    //ˆ—‚È‚µ
}

void Sound::MainthemaSound(bool playORstopflg)
{
    if (playORstopflg == true)
    {
        PlaySoundMem(isMainthemaHandle, DX_PLAYTYPE_LOOP, TRUE);
    }
    else
    {
        StopSoundMem(isMainthemaHandle);
    }
}

void Sound::LastspurtSound(bool playORstopflg)
{
    if (playORstopflg == true)
    {
        PlaySoundMem(isLastspurtHandle, DX_PLAYTYPE_LOOP, TRUE);
    }
    else
    {
        StopSoundMem(isLastspurtHandle);
    }
}
void Sound::UpSound()
{
    PlaySoundMem(isUpsoundHandle, DX_PLAYTYPE_BACK, TRUE);
}
void Sound::DeadSound(bool playORstopflg)
{
    if(playORstopflg == true)
    {
        PlaySoundMem(isDownsoundHandle, DX_PLAYTYPE_BACK, TRUE);
    }
    else
    {
         StopSoundMem(isDownsoundHandle);
    }
}
void Sound::StartSound()
{
    PlaySoundMem(isCatvoiceHandle, DX_PLAYTYPE_BACK, TRUE);
}
void Sound::ResultSound()
{
    PlaySoundMem(isClapHandle, DX_PLAYTYPE_BACK, TRUE);
}
void Sound::LastnoticeSound()
{
    PlaySoundMem(isLastnoticeHandle, DX_PLAYTYPE_BACK, TRUE);
}