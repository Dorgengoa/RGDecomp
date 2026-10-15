#include "types.h"

extern void TreasureBoxParamRefreshCondsMaybe_3eca40(void *, s32);
extern void PartySelectEncounter_3c9c30(s32);
extern void CharaSysEncounterDistRoll_3a59d0(s32, s32);
extern s32 PartyRefreshBgmOverride_3ca730(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x18];
    s32 m18;
    u8 pad01C[0x4];
    s32 m20;
    u8 pad024[0x8];
    u8 m2C;
};

s32 WorldOnStateFlag2Changed_3ed9a0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    u8 t0;
    s32 rv4;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 r3;

    t0 = p0->m2C;
    rv4 = 1;
    if ((t0 & 1) != 0) {
        rv4 = 0;
    } else {
        if ((p2 & 0xFF) != (p3 & 0xFF)) {
            TreasureBoxParamRefreshCondsMaybe_3eca40(p0, -1);
            t1 = p0->m18;
            PartySelectEncounter_3c9c30(t1);
            t2 = p0->m20;
            CharaSysEncounterDistRoll_3a59d0(t2, 0);
            t3 = p0->m18;
            r3 = PartyRefreshBgmOverride_3ca730(t3);
        }
        rv4 = 1;
    }
    return rv4;
}
