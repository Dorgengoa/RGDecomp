#include "types.h"

extern void CharaMgrPoolBroadcastPhase_3a87f0(s32, s32);
extern void ObjMgrBroadcastPhase_3ba9a0(s32, s32);
extern void InvBroadcastPhase_3c02b0(s32, s32);
extern s32 CharaSysOnBattleEnd_3a11f0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    s32 m18;
    s32 m1C;
    struct Obj1 *m20;
};

struct Obj1 {
    u8 pad000[0x24C];
    u8 m24C;
};

s32 GameDataBattleBroadcastPhase_3e6890(struct Obj0 *p0, s32 p1)
{
    struct Obj1 * t0;
    u8 t1;
    s32 rv7;
    s32 t2;
    s32 rv1;
    s32 t3;
    s32 t4;
    s32 rv3;
    s32 t5;
    s32 t6;
    struct Obj1 * rv5;
    struct Obj1 * t7;
    struct Obj1 * t8;
    s32 r6;

    t0 = p0->m20;
    t1 = p0->m20->m24C;
    rv7 = 1;
    if ((t1 & 1) == 0) {
        rv7 = 0;
    } else {
        t2 = p0->m14;
        if (t2 != 0) {
            CharaMgrPoolBroadcastPhase_3a87f0(t2, p1);
            t3 = p0->m1C;
            rv1 = t3;
        } else {
            t4 = p0->m1C;
            rv1 = t4;
        }
        if (rv1 != 0) {
            ObjMgrBroadcastPhase_3ba9a0(rv1, p1);
            t5 = p0->m18;
            rv3 = t5;
        } else {
            t6 = p0->m18;
            rv3 = t6;
        }
        if (rv3 != 0) {
            InvBroadcastPhase_3c02b0(rv3, p1);
            t7 = p0->m20;
            rv5 = t7;
        } else {
            t8 = p0->m20;
            rv5 = t8;
        }
        if (rv5 != 0) {
            r6 = CharaSysOnBattleEnd_3a11f0(rv5, p1);
        }
        rv7 = 1;
    }
    return rv7;
}
