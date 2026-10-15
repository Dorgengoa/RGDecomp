#include "types.h"

extern s32 GetEffectMgr_2d9040(void);
extern void EffectReleaseNodesByKey_2e1250(s32, s32, s32);
extern void TargetRefClear_2e71d0(s32);
extern void SwordTrailStop_2d7620(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x3F4];
    s32 m3F4;
    u8 pad3F8[0x2C];
    s16 m424;
    u8 pad426[0x15E];
    s32 m584;
    s32 m588;
    u8 pad58C[0x4CC];
    s16 mA58;
    s16 mA5A;
};

void CharaClearActionEffects_214ce0(struct Obj0 *p0)
{
    s32 r0;
    s16 t0;
    s32 t1;
    s32 rv2;
    s32 rv3;
    s32 t2;
    s32 t3;
    s32 l4;
    s32 l5;

    r0 = GetEffectMgr_2d9040();
    t0 = p0->m424;
    EffectReleaseNodesByKey_2e1250(r0, t0, 0xBB8);
    t1 = p0->m3F4;
    rv3 = t1;
    if (t1 != 0) {
        p0->mA58 = -1;
        p0->mA5A = -1;
        t2 = p0->m584;
        rv2 = t2;
        rv3 = -1;
    } else {
        t3 = p0->m584;
        rv2 = t3;
        rv3 = t1;
    }
    if (rv2 != 0) {
        l4 = 0;
        l5 = rv2;
        while (l4 < p0->m588) {
            TargetRefClear_2e71d0((l5 + 0x30));
            TargetRefClear_2e71d0((l5 + 0x60));
            SwordTrailStop_2d7620(l5);
            l4 = (l4 + 1);
            l5 = (l5 + 0xB8);
        }
        return;
    }
}
