#include "types.h"

extern s32 ScriptGetInt_26a2a0(void);
extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern void SoundPlayScaledVolume_1b9520(s32 a, s32 b, s32 c, f32 t);

s32 EvCmdSysSePlay_265b60(void)
{
    s32 m;

    m = ScriptGetInt_26a2a0();
    switch (m) {
    case 0:
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
        return 1;
    case 1:
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 6, 0, 1.0f);
        return 1;
    case 2:
        return 1;
    case 3:
        return 1;
    }
    return 0;
}
