#include "types.h"

extern s32 GetAttackChain_1fdb40(void);
extern s32 AttackChainReleaseHit_382bf0(s32);
extern s32 ScriptSetRefInt_26a1e0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdAttackChainReleaseHit_259250(s32 p0, s32 p1)
{
    s32 rv3;
    s32 r0;
    s32 r1;
    s32 r2;

    rv3 = 1;
    if (p1 <= 0) {
        rv3 = 0;
    } else {
        r0 = GetAttackChain_1fdb40();
        r1 = AttackChainReleaseHit_382bf0(r0);
        r2 = ScriptSetRefInt_26a1e0(p0, (r1 & 0xFF));
        rv3 = 1;
    }
    return rv3;
}
