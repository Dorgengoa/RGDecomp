#include "types.h"

extern void CharaResetActionState_21ea00(void *);
extern void CharaMoveReqResetThunk_2194d0(void *);
extern void CharaStopLoopSe_213bf0(void *);
extern void CharaStopLoopFg_213b60(void *);
extern s32 GetEffectMgr_2d9040(void);
extern s32 CharaGetId_214a80(void *);
extern void EffectReleaseNodesByKey_2e1250(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xA32];
    s16 mA32;
};

void CharaSetActionModeDeath_217d70(struct Obj0 *p0)
{
    s32 r4;
    s32 r5;

    p0->mA32 = 0x11;
    CharaResetActionState_21ea00(p0);
    CharaMoveReqResetThunk_2194d0((struct Obj0 *)((u8 *)p0 + 0x930));
    CharaStopLoopSe_213bf0(p0);
    CharaStopLoopFg_213b60(p0);
    r4 = GetEffectMgr_2d9040();
    r5 = CharaGetId_214a80(p0);
    EffectReleaseNodesByKey_2e1250(r4, r5, 0x1B58);
}
