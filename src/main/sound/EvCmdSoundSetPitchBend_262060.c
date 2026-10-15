#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

extern s32  ScriptGetInt_26a2a0(R8 *p);
extern void SoundSetPitchBend_1b8360(s32 a, s32 b, s32 c, s32 d);

s32 EvCmdSoundSetPitchBend_262060(R8 *q)
{
    s32 a;
    s32 b;
    s32 c;

    a = ScriptGetInt_26a2a0(q++);
    b = ScriptGetInt_26a2a0(q++);
    c = ScriptGetInt_26a2a0(q++);
    SoundSetPitchBend_1b8360(a, b, c, 0);
    return 1;
}
