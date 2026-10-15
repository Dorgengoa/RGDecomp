#include "types.h"

extern void SoundSetEntryVolume_1b87c0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void SoundSetEntryVolumeScaled_1b9820(s32 arg0, s32 arg1, s32 arg2, f32 arg3);
extern f32 TaggedGetFloat_26a280(s32 arg0);
extern s32 ScriptGetInt_26a2a0(s32 arg0);

s32 EvCmdSoundSetEntryVolume_262140(s64 *arg0)
{
    s32 a;
    s32 b;

    a = ScriptGetInt_26a2a0((s32)arg0++);
    b = ScriptGetInt_26a2a0((s32)arg0++);
    switch (*(s32 *)arg0) {
    case 0:
        SoundSetEntryVolume_1b87c0(a, b, ScriptGetInt_26a2a0((s32)arg0), 0);
        break;
    case 1:
        SoundSetEntryVolumeScaled_1b9820(a, b, 0, TaggedGetFloat_26a280((s32)arg0));
        break;
    default:
        return 0;

    }
    return 1;
}
