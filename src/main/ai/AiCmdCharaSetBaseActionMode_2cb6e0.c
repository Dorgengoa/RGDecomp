#include "types.h"

extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 CharaSetBaseActionMode_213820(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004DB92C;

s32 AiCmdCharaSetBaseActionMode_2cb6e0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptSlotGetInt_2cc9c0(p0);
    r1 = CharaSetBaseActionMode_213820(D_004DB92C, r0);
    return 1;
}
