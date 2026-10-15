#include "types.h"

typedef struct E8_FUN_00262370 {
    s32 a;
    s32 b;
} E8_FUN_00262370;

extern void *ScriptGetInt_26a2a0(E8_FUN_00262370 *p);
extern void SoundPauseEntry_1b9360(void *a, void *b);

s32 EvCmdSoundPauseEntry_262370(E8_FUN_00262370 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_26a2a0(q++);
    b = ScriptGetInt_26a2a0(q);
    SoundPauseEntry_1b9360(a, b);
    return 1;
}
